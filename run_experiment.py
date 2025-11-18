"""
Run experiments and generate analysis plots
EIC2_12 - Urban Parking Management Simulation
"""

import pandas as pd
import matplotlib.pyplot as plt
from parking_simulation import ParkingLotModel


def run_single_experiment(steps=200, **model_params):
    """Run a single experiment with given parameters"""
    model = ParkingLotModel(**model_params)

    print(f"Running experiment for {steps} steps...")
    for i in range(steps):
        model.step()
        if i % 50 == 0:
            print(f"  Step {i}/{steps} - Occupancy: {model.get_occupancy():.2%}")

    return model


def generate_plots(model, filename_prefix="simulation"):
    """Generate analysis plots from model data"""
    df = model.datacollector.get_model_vars_dataframe()

    # Create figure with subplots
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    fig.suptitle('Parking Lot Simulation Analysis - EIC2_12', fontsize=16, fontweight='bold')

    # Plot 1: Occupancy over time
    ax1 = axes[0, 0]
    df[['Occupancy', 'General Occupancy', 'EV Occupancy', 'PMR Occupancy']].plot(ax=ax1)
    ax1.set_title('Occupancy Rates Over Time')
    ax1.set_xlabel('Simulation Step')
    ax1.set_ylabel('Occupancy Rate')
    ax1.legend(['Overall', 'General', 'EV', 'PMR'])
    ax1.grid(True, alpha=0.3)

    # Plot 2: Cumulative arrivals, parking, exits
    ax2 = axes[0, 1]
    df[['Cars Arrived', 'Cars Parked', 'Cars Exited']].plot(ax=ax2)
    ax2.set_title('Cumulative Vehicle Flow')
    ax2.set_xlabel('Simulation Step')
    ax2.set_ylabel('Number of Cars')
    ax2.legend(['Arrived', 'Parked', 'Exited'])
    ax2.grid(True, alpha=0.3)

    # Plot 3: Cars in system (arrived - exited)
    ax3 = axes[1, 0]
    df['Cars in System'] = df['Cars Arrived'] - df['Cars Exited']
    df['Cars in System'].plot(ax=ax3, color='purple', linewidth=2)
    ax3.set_title('Cars Currently in System')
    ax3.set_xlabel('Simulation Step')
    ax3.set_ylabel('Number of Cars')
    ax3.grid(True, alpha=0.3)

    # Plot 4: Rolling average occupancy (last 20 steps)
    ax4 = axes[1, 1]
    df['Occupancy'].rolling(window=20).mean().plot(ax=ax4, color='darkblue', linewidth=2)
    ax4.set_title('Rolling Average Occupancy (20-step window)')
    ax4.set_xlabel('Simulation Step')
    ax4.set_ylabel('Occupancy Rate')
    ax4.grid(True, alpha=0.3)

    plt.tight_layout()

    # Save plot
    plot_filename = f"{filename_prefix}_analysis.png"
    plt.savefig(plot_filename, dpi=150, bbox_inches='tight')
    print(f"\nPlot saved to: {plot_filename}")

    # Save data to CSV
    csv_filename = f"{filename_prefix}_data.csv"
    df.to_csv(csv_filename)
    print(f"Data saved to: {csv_filename}")

    return df


def print_summary_statistics(model, df):
    """Print summary statistics from the simulation"""
    print("\n" + "=" * 60)
    print("SIMULATION SUMMARY STATISTICS")
    print("=" * 60)

    print("\nVehicle Flow:")
    print(f"  Total cars arrived:      {model.cars_arrived}")
    print(f"  Total cars parked:       {model.cars_parked}")
    print(f"  Total cars exited:       {model.cars_exited}")
    print(f"  Cars still in system:    {model.cars_arrived - model.cars_exited}")

    print("\nOccupancy Statistics:")
    print(f"  Final occupancy:         {model.get_occupancy():.2%}")
    print(f"  Average occupancy:       {df['Occupancy'].mean():.2%}")
    print(f"  Max occupancy:           {df['Occupancy'].max():.2%}")
    print(f"  Min occupancy:           {df['Occupancy'].min():.2%}")

    print("\nOccupancy by Type (Final):")
    print(f"  General spaces:          {model.get_occupancy_by_type(model.schedule.agents[0].space_type if hasattr(model.schedule.agents[0], 'space_type') else None):.2%}")

    print("\nCapacity:")
    print(f"  General spaces:          {model.n_general_spaces}")
    print(f"  EV spaces:               {model.n_ev_spaces}")
    print(f"  PMR spaces:              {model.n_pmr_spaces}")
    print(f"  Total capacity:          {model.n_general_spaces + model.n_ev_spaces + model.n_pmr_spaces}")

    print("\nModel Parameters:")
    print(f"  Arrival rate:            {model.arrival_rate}")
    print(f"  Mean dwell time:         {model.mean_dwell_time} steps")
    print(f"  Probability General:     {model.prob_general}")
    print(f"  Probability EV:          {model.prob_ev}")
    print(f"  Probability PMR:         {model.prob_pmr}")

    print("=" * 60 + "\n")


def compare_scenarios():
    """Compare different scenarios (e.g., different arrival rates)"""
    print("\n" + "=" * 60)
    print("COMPARING DIFFERENT ARRIVAL RATE SCENARIOS")
    print("=" * 60)

    scenarios = [
        {"name": "Low Demand", "arrival_rate": 0.2},
        {"name": "Medium Demand", "arrival_rate": 0.4},
        {"name": "High Demand", "arrival_rate": 0.6},
    ]

    results = []

    for scenario in scenarios:
        print(f"\nRunning scenario: {scenario['name']}")
        model = run_single_experiment(steps=200, arrival_rate=scenario['arrival_rate'])
        df = model.datacollector.get_model_vars_dataframe()

        results.append({
            'Scenario': scenario['name'],
            'Arrival Rate': scenario['arrival_rate'],
            'Avg Occupancy': df['Occupancy'].mean(),
            'Max Occupancy': df['Occupancy'].max(),
            'Total Arrived': model.cars_arrived,
            'Total Parked': model.cars_parked,
            'Total Exited': model.cars_exited,
        })

    # Create comparison dataframe
    comparison_df = pd.DataFrame(results)
    print("\n" + "=" * 60)
    print("SCENARIO COMPARISON")
    print("=" * 60)
    print(comparison_df.to_string(index=False))
    print()

    # Save comparison
    comparison_df.to_csv('scenario_comparison.csv', index=False)
    print("Scenario comparison saved to: scenario_comparison.csv\n")

    # Plot comparison
    fig, axes = plt.subplots(1, 2, figsize=(12, 5))
    fig.suptitle('Scenario Comparison - EIC2_12', fontsize=14, fontweight='bold')

    # Occupancy comparison
    comparison_df.plot(x='Scenario', y=['Avg Occupancy', 'Max Occupancy'],
                       kind='bar', ax=axes[0], rot=0)
    axes[0].set_title('Occupancy by Scenario')
    axes[0].set_ylabel('Occupancy Rate')
    axes[0].legend(['Average', 'Maximum'])

    # Flow comparison
    comparison_df.plot(x='Scenario', y=['Total Arrived', 'Total Parked', 'Total Exited'],
                       kind='bar', ax=axes[1], rot=0)
    axes[1].set_title('Vehicle Flow by Scenario')
    axes[1].set_ylabel('Number of Vehicles')
    axes[1].legend(['Arrived', 'Parked', 'Exited'])

    plt.tight_layout()
    plt.savefig('scenario_comparison.png', dpi=150, bbox_inches='tight')
    print("Comparison plot saved to: scenario_comparison.png\n")


if __name__ == "__main__":
    print("=" * 60)
    print("PARKING LOT SIMULATION - EXPERIMENT RUNNER")
    print("EIC2_12 - Urban Parking Management")
    print("=" * 60)

    # Example 1: Run single experiment
    print("\n### EXPERIMENT 1: Single Run with Default Parameters ###\n")
    model = run_single_experiment(
        steps=200,
        n_general_spaces=30,
        n_ev_spaces=10,
        n_pmr_spaces=5,
        arrival_rate=0.4,
        mean_dwell_time=20
    )

    df = generate_plots(model, filename_prefix="experiment1")
    print_summary_statistics(model, df)

    # Example 2: Compare scenarios
    print("\n### EXPERIMENT 2: Scenario Comparison ###\n")
    compare_scenarios()

    print("\n" + "=" * 60)
    print("All experiments complete!")
    print("Check the generated PNG and CSV files for results.")
    print("=" * 60)
