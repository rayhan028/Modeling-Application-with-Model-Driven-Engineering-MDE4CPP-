import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
df = pd.read_csv('ClinicModel_times.csv')

# Remove leading/trailing whitespace (if needed)
df.columns = df.columns.str.strip()

# Create a figure with two subplots side by side
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 5))  # 1 row, 2 columns

# Plot 1: Num_Elements vs Creation Time
ax1.plot(df['CreationTime_Ms'], df['Num_Elements'], marker='o') # Using 'CreationTime_Ms' and 'Num_Elements'
ax1.set_title('Num_Elements vs Creation Time')
ax1.set_xlabel('Creation Time (ms)')
ax1.set_ylabel('Num_Elements')
ax1.grid(True)

# Plot 2: Num_Elements vs Deletion Time
ax2.plot(df['DeletionTime_Ms'], df['Num_Elements'], marker='o') # Using 'DeletionTime_Ms' and 'Num_Elements'
ax2.set_title('Num_Elements vs Deletion Time')
ax2.set_xlabel('Deletion Time (ms)')
ax2.set_ylabel('Num_Elements')
ax2.grid(True)

plt.tight_layout() 
plt.show()