import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv('ClinicModel_times.csv')

grouped = df.groupby('Num_Elements').agg(['mean', 'std'])

# individual time
num_elements = grouped.index  # X-axis values

time1_means = grouped['Time1']['mean']
time1_stds = grouped['Time1']['std']

time2_means = grouped['Time2']['mean']
time2_stds = grouped['Time2']['std']

time3_means = grouped['Time3']['mean']
time3_stds = grouped['Time3']['std']

time4_means = grouped['Time4']['mean']
time4_stds = grouped['Time4']['std']

time5_means = grouped['Time5']['mean']
time5_stds = grouped['Time5']['std']

time6_means = grouped['Time6']['mean']
time6_stds = grouped['Time6']['std']

time7_means = grouped['Time7']['mean']
time7_stds = grouped['Time7']['std']

# Deletion time statistics
deletion_means = grouped['DeletionTime']['mean']
deletion_stds = grouped['DeletionTime']['std']

color1 = '#336699'
color2 = '#ff6600'
color3 = '#009933'
color4 = '#663300'
color_deletion = '#ff5050' 
color_deletion = '#ff5050'
# Plotting results
plt.figure(figsize=(12, 6))

# Plot each operation time manually
plt.errorbar(num_elements, time1_means, yerr=time1_stds, label='Staff_creation', fmt='-o', markersize=8, capsize=5, color=color1)
plt.errorbar(num_elements, time2_means, yerr=time2_stds, label='Specialized Facility creation', fmt='-D', markersize=8, capsize=5, color=color2)
plt.errorbar(num_elements, time3_means, yerr=time3_stds, label='General Facility creation', fmt='-s', markersize=8, capsize=5, color=color3)
plt.errorbar(num_elements, time4_means, yerr=time4_stds, label='Administration Facility creation', fmt='-^', markersize=8, capsize=5, color=color4)


# Plot deletion time
plt.errorbar(num_elements, deletion_means, yerr=deletion_stds, label='Deletion Time', fmt='-s', capsize=5, color='red')

# Labels and title
plt.xlabel('UML Model Element Instances', fontsize=12)
plt.ylabel('Time (microseconds)', fontsize=12)
plt.title('Performance Metrics of UML Operations and Deletion Time', fontsize=14)
plt.legend(fontsize=10)
plt.grid(True, linestyle='--', alpha=0.6)

plt.xticks(num_elements[::2], fontsize=10, rotation=30)  # Show every 2nd Num_Elements value
plt.tight_layout()
plt.savefig('Figure_1.png', dpi=300, bbox_inches='tight')

# Show plot
plt.show()
