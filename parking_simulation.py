"""
Parking Lot Simulation using Mesa
EIC2_12 - Urban Parking Management Simulation
"""

import mesa
import random
from enum import Enum


class VehicleType(Enum):
    """Types of vehicles in the simulation"""
    GENERAL = "GEN"
    ELECTRIC = "EV"
    REDUCED_MOBILITY = "PMR"


class DriverState(Enum):
    """States that a driver can be in"""
    ARRIVING_QUEUE = "ARRIVING_QUEUE"
    ENTERING_GATE = "ENTERING_GATE"
    SEARCHING = "SEARCHING"
    PARKED = "PARKED"
    HEADING_TO_EXIT = "HEADING_TO_EXIT"
    EXIT_QUEUE = "EXIT_QUEUE"
    EXITED = "EXITED"


class ParkingSpace(mesa.Agent):
    """Represents a parking space in the lot"""

    def __init__(self, unique_id, model, space_type):
        super().__init__(unique_id, model)
        self.space_type = space_type  # VehicleType
        self.occupied = False
        self.reserved_for = None  # Can hold a Car agent if reserved

    def step(self):
        """Parking spaces are passive - they don't take actions"""
        pass


class Car(mesa.Agent):
    """Represents a car/driver agent"""

    def __init__(self, unique_id, model, vehicle_type, arrival_time, dwell_time):
        super().__init__(unique_id, model)
        self.vehicle_type = vehicle_type
        self.arrival_time = arrival_time
        self.dwell_time = dwell_time  # How long they want to park
        self.state = DriverState.SEARCHING
        self.assigned_space = None
        self.parked_at_time = None
        self.target_pos = None

    def step(self):
        """Execute one step of the car's behavior"""
        if self.state == DriverState.SEARCHING:
            self.search_for_parking()
        elif self.state == DriverState.PARKED:
            self.check_departure()
        elif self.state == DriverState.HEADING_TO_EXIT:
            self.exit_parking()

    def search_for_parking(self):
        """Look for an available parking space"""
        # Find available parking spaces that match vehicle type
        available_spaces = [
            agent for agent in self.model.schedule.agents
            if isinstance(agent, ParkingSpace)
            and not agent.occupied
            and agent.space_type == self.vehicle_type
        ]

        if available_spaces:
            # Park in a random available space
            space = random.choice(available_spaces)
            self.park_in_space(space)
        else:
            # Move randomly while searching
            self.move_randomly()

    def park_in_space(self, space):
        """Park the car in the given space"""
        space.occupied = True
        self.assigned_space = space
        self.state = DriverState.PARKED
        self.parked_at_time = self.model.schedule.steps

        # Move to the parking space location
        if hasattr(self.model, 'grid'):
            self.model.grid.move_agent(self, space.pos)

        # Update statistics
        self.model.cars_parked += 1

    def check_departure(self):
        """Check if it's time to leave"""
        if self.model.schedule.steps - self.parked_at_time >= self.dwell_time:
            self.leave_parking()

    def leave_parking(self):
        """Leave the parking space"""
        if self.assigned_space:
            self.assigned_space.occupied = False
            self.assigned_space = None
        self.state = DriverState.HEADING_TO_EXIT

    def exit_parking(self):
        """Exit the parking lot"""
        self.state = DriverState.EXITED
        self.model.cars_exited += 1
        # Remove from grid
        if hasattr(self.model, 'grid'):
            self.model.grid.remove_agent(self)
        # Remove from schedule
        self.model.schedule.remove(self)

    def move_randomly(self):
        """Move to a random neighboring cell"""
        if hasattr(self.model, 'grid'):
            possible_steps = self.model.grid.get_neighborhood(
                self.pos,
                moore=True,
                include_center=False
            )
            new_position = random.choice(possible_steps)
            self.model.grid.move_agent(self, new_position)


class ParkingLotModel(mesa.Model):
    """
    A model simulating a parking lot with different types of spaces
    and vehicles arriving with stochastic patterns.
    """

    def __init__(
        self,
        width=20,
        height=20,
        n_general_spaces=30,
        n_ev_spaces=10,
        n_pmr_spaces=5,
        arrival_rate=0.3,
        prob_general=0.7,
        prob_ev=0.2,
        prob_pmr=0.1,
        mean_dwell_time=20
    ):
        super().__init__()
        self.width = width
        self.height = height
        self.n_general_spaces = n_general_spaces
        self.n_ev_spaces = n_ev_spaces
        self.n_pmr_spaces = n_pmr_spaces
        self.arrival_rate = arrival_rate
        self.prob_general = prob_general
        self.prob_ev = prob_ev
        self.prob_pmr = prob_pmr
        self.mean_dwell_time = mean_dwell_time

        # Statistics
        self.cars_arrived = 0
        self.cars_parked = 0
        self.cars_exited = 0
        self.cars_turned_away = 0

        # Create grid and schedule
        self.grid = mesa.space.MultiGrid(width, height, torus=False)
        self.schedule = mesa.time.RandomActivation(self)

        # Counter for unique IDs
        self.next_id = 0

        # Create parking spaces
        self._create_parking_spaces()

        # Data collector for tracking KPIs
        self.datacollector = mesa.DataCollector(
            model_reporters={
                "Cars Arrived": lambda m: m.cars_arrived,
                "Cars Parked": lambda m: m.cars_parked,
                "Cars Exited": lambda m: m.cars_exited,
                "Occupancy": self.get_occupancy,
                "General Occupancy": lambda m: m.get_occupancy_by_type(VehicleType.GENERAL),
                "EV Occupancy": lambda m: m.get_occupancy_by_type(VehicleType.ELECTRIC),
                "PMR Occupancy": lambda m: m.get_occupancy_by_type(VehicleType.REDUCED_MOBILITY),
            }
        )

    def _create_parking_spaces(self):
        """Create parking spaces in designated areas of the grid"""
        # General spaces (left side)
        self._place_spaces(VehicleType.GENERAL, self.n_general_spaces, 1, 1, 8, 8)

        # EV spaces (top middle)
        self._place_spaces(VehicleType.ELECTRIC, self.n_ev_spaces, 10, 1, 15, 4)

        # PMR spaces (bottom middle)
        self._place_spaces(VehicleType.REDUCED_MOBILITY, self.n_pmr_spaces, 10, 6, 15, 8)

    def _place_spaces(self, space_type, count, x_min, y_min, x_max, y_max):
        """Place parking spaces in a rectangular area"""
        placed = 0
        attempts = 0
        max_attempts = count * 10

        while placed < count and attempts < max_attempts:
            x = random.randint(x_min, min(x_max, self.width - 1))
            y = random.randint(y_min, min(y_max, self.height - 1))

            # Check if position is empty
            cell_contents = self.grid.get_cell_list_contents([(x, y)])
            if not any(isinstance(agent, ParkingSpace) for agent in cell_contents):
                space = ParkingSpace(self.next_id, self, space_type)
                self.next_id += 1
                self.grid.place_agent(space, (x, y))
                self.schedule.add(space)
                placed += 1

            attempts += 1

    def generate_arrival(self):
        """Stochastically generate new car arrivals"""
        if random.random() < self.arrival_rate:
            # Determine vehicle type
            rand = random.random()
            if rand < self.prob_general:
                vehicle_type = VehicleType.GENERAL
            elif rand < self.prob_general + self.prob_ev:
                vehicle_type = VehicleType.ELECTRIC
            else:
                vehicle_type = VehicleType.REDUCED_MOBILITY

            # Generate dwell time (exponential distribution)
            dwell_time = int(random.expovariate(1 / self.mean_dwell_time)) + 1

            # Create new car
            car = Car(
                self.next_id,
                self,
                vehicle_type,
                self.schedule.steps,
                dwell_time
            )
            self.next_id += 1
            self.cars_arrived += 1

            # Place car at a random entry point (right edge)
            x = self.width - 1
            y = random.randint(0, self.height - 1)
            self.grid.place_agent(car, (x, y))
            self.schedule.add(car)

    def get_occupancy(self):
        """Calculate overall occupancy rate"""
        total_spaces = self.n_general_spaces + self.n_ev_spaces + self.n_pmr_spaces
        if total_spaces == 0:
            return 0

        occupied_count = sum(
            1 for agent in self.schedule.agents
            if isinstance(agent, ParkingSpace) and agent.occupied
        )
        return occupied_count / total_spaces

    def get_occupancy_by_type(self, vehicle_type):
        """Calculate occupancy rate for a specific vehicle type"""
        spaces = [
            agent for agent in self.schedule.agents
            if isinstance(agent, ParkingSpace) and agent.space_type == vehicle_type
        ]
        if not spaces:
            return 0

        occupied = sum(1 for space in spaces if space.occupied)
        return occupied / len(spaces)

    def step(self):
        """Advance the model by one step"""
        # Generate new arrivals
        self.generate_arrival()

        # Execute agent steps
        self.schedule.step()

        # Collect data
        self.datacollector.collect(self)


# Simple visualization portrayal
def agent_portrayal(agent):
    """Define how agents are displayed in the visualization"""
    if isinstance(agent, ParkingSpace):
        if agent.space_type == VehicleType.GENERAL:
            color = "#90EE90" if not agent.occupied else "#006400"  # Light/Dark Green
            shape = "rect"
        elif agent.space_type == VehicleType.ELECTRIC:
            color = "#87CEEB" if not agent.occupied else "#00008B"  # Light/Dark Blue
            shape = "rect"
        else:  # PMR
            color = "#FFB6C1" if not agent.occupied else "#8B0000"  # Light/Dark Red
            shape = "rect"

        return {
            "Shape": shape,
            "Color": color,
            "Filled": "true",
            "Layer": 0,
            "w": 0.8,
            "h": 0.8
        }

    elif isinstance(agent, Car):
        if agent.state == DriverState.PARKED:
            return None  # Don't show parked cars (they're in spaces)

        # Show searching cars
        if agent.vehicle_type == VehicleType.GENERAL:
            color = "#FFD700"  # Gold
        elif agent.vehicle_type == VehicleType.ELECTRIC:
            color = "#00BFFF"  # Deep Sky Blue
        else:  # PMR
            color = "#FF69B4"  # Hot Pink

        return {
            "Shape": "circle",
            "Color": color,
            "Filled": "true",
            "Layer": 1,
            "r": 0.5
        }

    return {}


if __name__ == "__main__":
    # Create and run a simple model
    print("Creating parking lot simulation...")
    model = ParkingLotModel(
        width=20,
        height=20,
        n_general_spaces=30,
        n_ev_spaces=10,
        n_pmr_spaces=5,
        arrival_rate=0.4,
        mean_dwell_time=20
    )

    print(f"Running simulation for 100 steps...")
    for i in range(100):
        model.step()
        if i % 10 == 0:
            print(f"Step {i}: Occupancy = {model.get_occupancy():.2%}, "
                  f"Cars: {model.cars_arrived} arrived, {model.cars_parked} parked, "
                  f"{model.cars_exited} exited")

    print("\nSimulation complete!")
    print(f"Final statistics:")
    print(f"  Total cars arrived: {model.cars_arrived}")
    print(f"  Total cars parked: {model.cars_parked}")
    print(f"  Total cars exited: {model.cars_exited}")
    print(f"  Final occupancy: {model.get_occupancy():.2%}")
