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

color1 = '#003399'
color2 = '#ff9966'
color3 = '#009933'

# Plotting results
plt.figure(figsize=(12, 6))

# Plot each operation time manually
plt.errorbar(num_elements, time5_means, yerr=time5_stds, label='NurseWorkplace coordination', fmt='-v', markersize=10, capsize=5, color=color1)
plt.errorbar(num_elements, time6_means, yerr=time6_stds, label='DoctorWorkplace coordination', fmt='-P', markersize=10, capsize=5, color=color2)
plt.errorbar(num_elements, time7_means, yerr=time7_stds, label='AdminWorkplace coordination', fmt='-*', markersize=10, capsize=5, color=color3)

# Plot deletion time
plt.errorbar(num_elements, deletion_means, yerr=deletion_stds, label='Deletion Time', fmt='-s', capsize=5, color='red')

# Labels and title
plt.xlabel('UML Model Element Instances', fontsize=12)
plt.ylabel('Time (microseconds)', fontsize=12)
plt.title('Performance Metrics of Search Operations and Deletion Time', fontsize=14)
plt.legend(fontsize=10)
plt.grid(True, linestyle='--', alpha=0.6)

plt.xticks(num_elements[::2], fontsize=10, rotation=30)  # Show every 2nd Num_Elements value
plt.tight_layout()
plt.savefig('Figure_1.png', dpi=300, bbox_inches='tight')

# Show plot
plt.show()
