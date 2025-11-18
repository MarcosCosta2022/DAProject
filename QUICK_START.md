# Quick Start Guide - Parking Lot Simulation

## What You Have Now

A complete Mesa-based parking lot simulation for your EIC2_12 assignment with:

✅ **Agent-based model** with Cars and Parking Spaces
✅ **3 vehicle types**: General, EV (Electric), PMR (Reduced Mobility)
✅ **Interactive visualization** in your browser
✅ **KPI tracking**: Occupancy, arrivals, exits
✅ **Experiment framework** for comparing scenarios
✅ **Data export** to CSV and plots

## Three Ways to Run

### 1. Simple Console Simulation (Quickest)
```bash
python3 parking_simulation.py
```
Runs 100 steps and prints statistics. Good for quick testing.

### 2. Interactive Browser Visualization (Recommended!)
```bash
python3 run_visualization.py
```
Then open: **http://localhost:8521**

Features:
- See cars moving in real-time
- Adjust parameters with sliders
- View live charts
- Control simulation speed
- Step through one at a time

### 3. Run Experiments & Generate Analysis
```bash
python3 run_experiment.py
```
Generates:
- `experiment1_analysis.png` - 4 plots analyzing the simulation
- `experiment1_data.csv` - Raw data for further analysis
- `scenario_comparison.png` - Comparison of different arrival rates
- `scenario_comparison.csv` - Summary statistics

## What Each File Does

| File | Purpose |
|------|---------|
| `parking_simulation.py` | Core model with all agents and logic |
| `run_visualization.py` | Web-based interactive visualization |
| `run_experiment.py` | Run experiments and generate analysis |
| `README_PARKING_SIMULATION.md` | Complete documentation |
| `QUICK_START.md` | This file |

## Color Legend for Visualization

**Parking Spaces (squares/rectangles):**
- 🟢 Light Green = Empty General Space
- 🟩 Dark Green = Occupied General Space
- 🔵 Light Blue = Empty EV Space
- 🔷 Dark Blue = Occupied EV Space
- 🌸 Light Pink = Empty PMR Space
- 🔴 Dark Red = Occupied PMR Space

**Moving Cars (circles):**
- 🟡 Gold = General vehicle searching
- 💙 Sky Blue = EV searching
- 💖 Hot Pink = PMR vehicle searching

## Next Steps for Your Assignment

Based on your Delivery 1, you should add:

1. **Entry/Exit Gates** with queuing
2. **Different allocation strategies**: FCFS, Pre-booking, Auction, Dynamic Pricing
3. **Internal circulation** with congestion
4. **More KPIs**: Time in system, turn-away rate, revenue
5. **Comparative analysis** of strategies

All the infrastructure is ready - you just need to extend it!

## Example: Modify Parameters

Edit `run_visualization.py` or `run_experiment.py`:

```python
model = ParkingLotModel(
    n_general_spaces=40,    # More spaces
    n_ev_spaces=15,
    arrival_rate=0.6,       # Higher demand
    mean_dwell_time=30      # Longer parking
)
```

## Getting Help

- Read `README_PARKING_SIMULATION.md` for detailed documentation
- Check your assignment PDF for requirements
- Extend the `Car.step()` and `ParkingLotModel.step()` methods for new behaviors

## Example Output

After running `run_experiment.py`, you'll have:
- Charts showing occupancy trends
- Cumulative flow statistics
- Comparison across scenarios
- CSV data for pandas/excel analysis

**Good luck with your assignment!** 🚗🅿️
