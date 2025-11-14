import pandas as pd
import matplotlib.pyplot as plt

# reading csv files 
df_creation = pd.read_csv('EcoreCreation_times.csv')
df_deletion = pd.read_csv('EcoreDeletion_times.csv')

# Mean and stdDev for Creation and Deletion Time
results1 = df_creation.groupby('RUN')['Creation_Time_ms'].agg(['mean', 'std']).sort_index()
results2 = df_deletion.groupby('RUN')['Deletion_Time_ms'].agg(['mean', 'std']).sort_index()

# Extract NUM_Object values in correct order
num_objects = df_creation.groupby('RUN')['NUM_Object'].first().sort_index().values

plt.figure(figsize=(10, 6))

color_creation = '#003399'
color_deletion = '#ff5050' 

# Plotting Creation Time
plt.errorbar( num_objects, results1['mean'], yerr=results1['std'], fmt='o-', capsize=8, capthick=2, elinewidth=2, markersize=9, label='Creation Time', color=color_creation, alpha=0.8)

# Plotting Deletion Time
plt.errorbar( num_objects, results2['mean'], yerr=results2['std'], fmt='o-', capsize=8, capthick=2, elinewidth=2, markersize=9, label='Deletion Time', color=color_deletion, alpha=0.8)

# Labels and Titles
plt.xlabel('Model Elements', fontsize=12)
plt.ylabel('Time (microseconds)', fontsize=12)
plt.title('Performance Metrics of Execution Time with Ecore Meta-Model', fontsize=14)

plt.xticks(num_objects, rotation=30, fontsize=10)
plt.yticks(fontsize=10)
plt.grid(True, linestyle='--', alpha=0.5)

# legend and layout adjustment
plt.legend(fontsize=12)
plt.tight_layout()

plt.savefig('Ecore_Performance_Metrics.png', dpi=300, bbox_inches='tight')

# Show plot
plt.show()