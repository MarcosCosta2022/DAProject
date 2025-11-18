"""
Run the parking lot simulation with interactive visualization
EIC2_12 - Urban Parking Management Simulation
"""

import mesa
from parking_simulation import ParkingLotModel, agent_portrayal


# Create canvas for visualization
grid = mesa.visualization.CanvasGrid(agent_portrayal, 20, 20, 600, 600)

# Create charts for KPIs
occupancy_chart = mesa.visualization.ChartModule(
    [
        {"Label": "Occupancy", "Color": "Black"},
        {"Label": "General Occupancy", "Color": "Green"},
        {"Label": "EV Occupancy", "Color": "Blue"},
        {"Label": "PMR Occupancy", "Color": "Red"},
    ],
    data_collector_name='datacollector'
)

arrival_chart = mesa.visualization.ChartModule(
    [
        {"Label": "Cars Arrived", "Color": "Orange"},
        {"Label": "Cars Parked", "Color": "Green"},
        {"Label": "Cars Exited", "Color": "Gray"},
    ],
    data_collector_name='datacollector'
)

# Model parameters that can be adjusted in the web interface
model_params = {
    "width": 20,
    "height": 20,
    "n_general_spaces": mesa.visualization.Slider(
        "Number of General Spaces",
        30,
        5,
        60,
        1,
        description="Total general parking spaces"
    ),
    "n_ev_spaces": mesa.visualization.Slider(
        "Number of EV Spaces",
        10,
        2,
        30,
        1,
        description="Total EV parking spaces"
    ),
    "n_pmr_spaces": mesa.visualization.Slider(
        "Number of PMR Spaces",
        5,
        2,
        20,
        1,
        description="Total PMR parking spaces"
    ),
    "arrival_rate": mesa.visualization.Slider(
        "Arrival Rate",
        0.4,
        0.0,
        1.0,
        0.05,
        description="Probability of new car arrival per step"
    ),
    "prob_general": mesa.visualization.Slider(
        "Probability General Vehicle",
        0.7,
        0.0,
        1.0,
        0.05,
        description="Probability vehicle is general type"
    ),
    "prob_ev": mesa.visualization.Slider(
        "Probability EV",
        0.2,
        0.0,
        1.0,
        0.05,
        description="Probability vehicle is EV"
    ),
    "prob_pmr": mesa.visualization.Slider(
        "Probability PMR",
        0.1,
        0.0,
        1.0,
        0.05,
        description="Probability vehicle is PMR"
    ),
    "mean_dwell_time": mesa.visualization.Slider(
        "Mean Dwell Time",
        20,
        5,
        100,
        5,
        description="Average parking duration (steps)"
    ),
}

# Create the server
server = mesa.visualization.ModularServer(
    ParkingLotModel,
    [grid, occupancy_chart, arrival_chart],
    "Parking Lot Simulation - EIC2_12",
    model_params
)

server.port = 8521  # Default Mesa port

if __name__ == "__main__":
    print("=" * 60)
    print("PARKING LOT SIMULATION - EIC2_12")
    print("Urban Parking Management System")
    print("=" * 60)
    print("\nStarting visualization server...")
    print("Open your browser and navigate to:")
    print("  http://localhost:8521")
    print("\nLegend:")
    print("  Parking Spaces:")
    print("    - Light Green = Empty General Space")
    print("    - Dark Green = Occupied General Space")
    print("    - Light Blue = Empty EV Space")
    print("    - Dark Blue = Occupied EV Space")
    print("    - Light Pink = Empty PMR Space")
    print("    - Dark Red = Occupied PMR Space")
    print("\n  Moving Cars (circles):")
    print("    - Gold = General vehicle searching")
    print("    - Sky Blue = EV searching")
    print("    - Hot Pink = PMR vehicle searching")
    print("\nPress Ctrl+C to stop the server")
    print("=" * 60)
    print()

    server.launch()
