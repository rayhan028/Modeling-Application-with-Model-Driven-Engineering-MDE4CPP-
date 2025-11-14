import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Read data from CSV file
df = pd.read_csv('resource_usage_log.csv')  
run = df["Num_of_Instance"].values
memory_use = df["Memory_use (MB)"].values
cpu_use = df["Avg_CPU_usage (%)"].values

# Insert (0,0,0) at the beginning
run = np.insert(run, 0, 0)
memory_use = np.insert(memory_use, 0, 0)
cpu_use = np.insert(cpu_use, 0, 0)

# Define colors
color1 = '#006666'
color2 = '#ff6600'

# Create figure and axis
fig, ax1 = plt.subplots(figsize=(12, 6))

# Plot Memory Usage
ax1.set_xlabel("Num. of Instances")
ax1.set_ylabel("Memory Use (MB)", color=color1)
ax1.plot(run, memory_use, 'o-', color=color1, label="Memory Use")
ax1.tick_params(axis='y', labelcolor=color1)

# Create second y-axis for CPU usage
ax2 = ax1.twinx()
ax2.set_ylabel("CPU Use (%)", color=color2)
ax2.plot(run, cpu_use, 's-', color=color2, label="CPU Use")
ax2.tick_params(axis='y', labelcolor=color2)

# Add grid
ax1.grid(True, linestyle='--', alpha=0.6)

# Set plot title
plt.title("Memory and CPU Usage for UML Application")

# Show plot
plt.show()

