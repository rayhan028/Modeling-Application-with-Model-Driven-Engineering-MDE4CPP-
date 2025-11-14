import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# reading csv file
df = pd.read_csv('ClinicModel_times.csv')

# Group by 'Num_Elements' and measuring mean and standard deviation for each group
grouped = df.groupby('Num_Elements').agg(['mean', 'std'])

time_columns = ['Time1', 'Time2', 'Time3', 'Time4', 'Time5', 'Time6', 'Time7'] # all operation times accross the row
time_means = grouped[time_columns].xs('mean', axis=1, level=1).mean(axis=1) # both of the values grouped together for visualization
time_stds = grouped[time_columns].xs('std', axis=1, level=1).mean(axis=1)

# deletion time measurement for each iteration of the program
deletion_means = grouped['DeletionTime']['mean']
deletion_stds = grouped['DeletionTime']['std']

# Plotting results 
num_elements = grouped.index  # Num_Elements as x-axis
plt.figure(figsize=(12, 6))

color_time = '#1f77b4'  # muted blue and red
color_deletion = '#d62728' 

# Plotting statistics measurement for all operation times defined in the model
plt.errorbar(num_elements, time_means, yerr=time_stds, label='UML Operation Time', fmt='-o', capsize=5, capthick=1, elinewidth=1, color=color_time, markersize=8)

# Plot for DeletionTime
plt.errorbar(num_elements, time_means,  label='DeletionTime', fmt='-o', capsize=5, capthick=1, elinewidth=1, color=color_deletion, markersize=8)

plt.errorbar(num_elements, time_stds,  label='DeletionTime', fmt='-o', capsize=5, capthick=1, elinewidth=1, color=color_deletion, markersize=8)


#plt.errorbar(num_elements, deletion_means, yerr=deletion_stds, label='DeletionTime', fmt='-o', capsize=5, capthick=1, elinewidth=1, color=color_deletion, markersize=8)

# labels and title
plt.xlabel('UML Model Element Instances', fontsize=12)
plt.ylabel('Time (microseconds)', fontsize=12)
plt.title('Performance Metrics of UML Operation and Deletion Time per Model Element Instances', fontsize=14)
plt.legend(fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)

plt.xticks(num_elements[::2], fontsize=12, rotation=30)  # Show every 2nd Num_Elements value with slight rotation to avoid cluttering
plt.tight_layout()
plt.savefig('Figure_1.png', dpi=300, bbox_inches='tight')
# Show plot
plt.show()

