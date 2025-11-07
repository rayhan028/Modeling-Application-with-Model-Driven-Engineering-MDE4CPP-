import pandas as pd
import matplotlib.pyplot as plt

# Reading benchmark data
df = pd.read_csv('MemoryData.csv')

# memory strings to float values 
df['Memory_Utilized(Ecore)'] = df['Memory_Utilized(Ecore)'].str.replace('MB', '').astype(float)
df['Memory Utilized(UML)'] = df['Memory Utilized(UML)'].str.replace('MB', '').astype(float)

# figure and axis objects with size
fig, ax1 = plt.subplots(figsize=(12, 8))

# Ecore data on primary y-axis
ax1.plot(df['Meta-Models'], df['Memory_Utilized(Ecore)'], 'b.-', label='Ecore')
ax1.set_xlabel('Number of Meta-Models (Ecore) / Model Elements (UML)')
ax1.set_ylabel('Memory Utilized (MB) - Ecore', color='blue')
ax1.tick_params(axis='y', labelcolor='blue')

# secondary y-axis for UML data
ax2 = ax1.twinx()
ax2.plot(df['Model_Elements'], df['Memory Utilized(UML)'], 'r.-', label='UML')
ax2.set_ylabel('Memory Utilized (MB) - UML', color='red')
ax2.tick_params(axis='y', labelcolor='red')

# graph title
plt.title('Memory Utilization of Ecore and UML Models')

# configuration
lines1, labels1 = ax1.get_legend_handles_labels()
lines2, labels2 = ax2.get_legend_handles_labels()
ax1.legend(lines1 + lines2, labels1 + labels2, loc='upper left')

# Adjusting UML Y-Axis Range for representable visualization
ax2.set_ylim(min(df['Memory Utilized(UML)']) - 5, max(df['Memory Utilized(UML)']) + 5) #adjust the 5 to what you feel is best for the data.

# to prevent label cutoff
plt.tight_layout()

# display plot
plt.show()
