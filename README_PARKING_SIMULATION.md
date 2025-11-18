# Parking Lot Simulation - EIC2_12

Urban Parking Management System using Mesa Agent-Based Modeling

## Overview

This simulation models a parking lot system with:
- **Agents**: Cars (drivers) and Parking Spaces
- **Vehicle Types**: General, Electric Vehicle (EV), Reduced Mobility (PMR)
- **Driver States**: Searching, Parked, Heading to Exit, Exited
- **KPIs**: Occupancy rates, arrival/parking/exit statistics

Based on your Delivery 1 assignment for Modelation and Simulation.

## Project Structure

```
parking_simulation.py      - Core simulation model with agents and logic
run_visualization.py       - Interactive web-based visualization
README_PARKING_SIMULATION.md - This file
```

## Quick Start

### 1. Run Command-Line Simulation (No Visualization)

```bash
python3 parking_simulation.py
```

This runs a 100-step simulation and prints statistics to the console.

### 2. Run Interactive Visualization (Browser-Based)

```bash
python3 run_visualization.py
```

Then open your browser to: **http://localhost:8521**

You'll see:
- **Grid View**: Parking lot with spaces and moving cars
- **Charts**: Real-time occupancy and arrival/exit statistics
- **Controls**: Start/Stop, Step-by-step, Reset
- **Sliders**: Adjust parameters on-the-fly

## Visualization Legend

### Parking Spaces (Rectangles)
- **Light Green** = Empty General Space
- **Dark Green** = Occupied General Space
- **Light Blue** = Empty EV Space
- **Dark Blue** = Occupied EV Space
- **Light Pink** = Empty PMR Space
- **Dark Red** = Occupied PMR Space

### Moving Cars (Circles)
- **Gold** = General vehicle searching for parking
- **Sky Blue** = EV searching for parking
- **Hot Pink** = PMR vehicle searching for parking

(Parked cars are not shown separately - they occupy the parking spaces)

## Model Components

### Agents

1. **ParkingSpace Agent**
   - Type: General, EV, or PMR
   - State: Occupied or Free
   - Location: Fixed position on grid

2. **Car Agent**
   - Vehicle Type: Matches parking space requirements
   - States: Searching → Parked → Heading to Exit → Exited
   - Arrival Time: Stochastic based on arrival rate
   - Dwell Time: How long they stay parked (exponential distribution)

### Model Parameters

You can adjust these in the web interface:

- **n_general_spaces** (30): Number of general parking spaces
- **n_ev_spaces** (10): Number of EV parking spaces
- **n_pmr_spaces** (5): Number of PMR parking spaces
- **arrival_rate** (0.4): Probability of new car arrival per step
- **prob_general** (0.7): Probability a new car is general type
- **prob_ev** (0.2): Probability a new car is EV
- **prob_pmr** (0.1): Probability a new car is PMR
- **mean_dwell_time** (20): Average parking duration in steps

### Key Performance Indicators (KPIs)

The simulation tracks:
- **Overall Occupancy**: Percentage of all spaces occupied
- **Type-Specific Occupancy**: Occupancy for General, EV, and PMR spaces
- **Cars Arrived**: Total vehicles that entered the system
- **Cars Parked**: Total vehicles that successfully found parking
- **Cars Exited**: Total vehicles that left after parking

## Next Steps for Your Assignment

Based on your Delivery 1 document, you can extend this simulation:

### 1. **Add Gate Queuing System**
   - Entry gates with service times
   - Exit gates with queues
   - Track wait times

### 2. **Implement Different Allocation Strategies**
   - First-Come-First-Serve (FCFS) - Currently implemented
   - Pre-booking/Reservation system
   - Auction-based allocation
   - Dynamic pricing

### 3. **Add Internal Circulation**
   - Congestion effects based on number of searching cars
   - Link travel times
   - Routing algorithms

### 4. **Enhanced Statistics**
   - Time in system (gate wait + search + park + exit)
   - Turn-away rate (when lot is full)
   - Revenue tracking (for pricing strategies)
   - Fairness metrics

### 5. **Data Collection & Analysis**
   - Export simulation data to CSV using Mesa's DataCollector
   - Create plots with matplotlib/seaborn
   - Compare strategies quantitatively

## Code Structure

### Core Classes

```python
# Enums
VehicleType: GENERAL, ELECTRIC, REDUCED_MOBILITY
DriverState: SEARCHING, PARKED, HEADING_TO_EXIT, EXITED

# Agents
ParkingSpace(mesa.Agent):
    - space_type: VehicleType
    - occupied: bool

Car(mesa.Agent):
    - vehicle_type: VehicleType
    - state: DriverState
    - dwell_time: int
    - search_for_parking()
    - park_in_space()
    - leave_parking()

# Model
ParkingLotModel(mesa.Model):
    - grid: MultiGrid
    - schedule: RandomActivation
    - datacollector: DataCollector
    - step(): Advance simulation
    - generate_arrival(): Create new cars
```

## Tips for Development

1. **Modify parameters** in `run_visualization.py` to change default values
2. **Add new KPIs** by extending the `datacollector` in `ParkingLotModel`
3. **Change grid layout** by modifying `_create_parking_spaces()` method
4. **Add new agent behaviors** by extending the `step()` methods
5. **Export data** using `model.datacollector.get_model_vars_dataframe()`

## Example: Export Data for Analysis

```python
import pandas as pd
from parking_simulation import ParkingLotModel

# Run simulation
model = ParkingLotModel()
for i in range(200):
    model.step()

# Get data
df = model.datacollector.get_model_vars_dataframe()
df.to_csv('simulation_results.csv')

# Plot
import matplotlib.pyplot as plt
df['Occupancy'].plot()
plt.title('Parking Lot Occupancy Over Time')
plt.xlabel('Step')
plt.ylabel('Occupancy Rate')
plt.savefig('occupancy_plot.png')
```

## Requirements

- Python 3.9+
- mesa
- numpy
- pandas
- matplotlib

Already installed in your environment!

## Good Luck!

This is a solid foundation for your assignment. You now have:
- ✅ Agent-based model with drivers and parking spaces
- ✅ Multiple vehicle types (General, EV, PMR)
- ✅ Interactive visualization
- ✅ KPI tracking
- ✅ Stochastic arrivals and dwell times

Ready to extend with gates, queues, and different allocation strategies!
