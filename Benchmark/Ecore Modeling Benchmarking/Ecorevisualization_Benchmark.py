import pandas as pd
import matplotlib.pyplot as plt

#the first file
df_creation = pd.read_csv('EcoreCreation_times.csv')
#mean and stddev for Creation Time
results1 = df_creation.groupby('RUN')['Creation_Time_ms'].agg(['mean', 'std'])

#the 2nd file
df_deletion = pd.read_csv('EcoreDeletion_times.csv')
#mean and stddev for deletion Time
results2 = df_deletion.groupby('RUN')['Deletion_Time_ms'].agg(['mean', 'std'])

df_uml= pd.read_csv('ClinicModel_times.csv');
result1= df_uml.groupby('Num_Elements')['Time1'].agg(['mean'])
result2= df_uml.groupby('Num_Elements')['Time2'].agg(['mean'])
result3= df_uml.groupby('Num_Elements')['Time3'].agg(['mean'])
result4= df_uml.groupby('Num_Elements')['Time4'].agg(['mean'])
result5= df_uml.groupby('Num_Elements')['Time5'].agg(['mean'])
# NUM_Object values in x-axis 

num_objects = df_creation.groupby('RUN')['NUM_Object'].first().values

num_objects2 = df_uml.groupby('RUN')['Num_Elements'].first().values

plt.figure(figsize=(10, 6))

# Plotting Creation Time
plt.errorbar(num_objects, results1['mean'], yerr=results1['std'], fmt='o-', capsize=5, label='Creation Time', color='blue')

# Plotting Deletion Time
#plt.errorbar(num_objects, results2['mean'], yerr=results2['std'], fmt='o-', capsize=5, label='Deletion Time', color='red')

plt.xlabel('(NUM_Object)')
plt.ylabel('Time (Mean and StdDev)')
plt.title('Mean Creation and Deletion Time with StdDev')
plt.xticks(num_objects)
plt.grid(True)
plt.legend()
plt.show()

print (num_objects2)
print (result1)


plt.figure(figsize=(10, 6))
plt.plot(num_objects2, result1['mean'], color='blue')
plt.plot(num_objects2, result2['mean'], color='red')
plt.plot(num_objects2, result3['mean'], color='green')
plt.plot(num_objects2, result4['mean'], color='black')
#plt.plot(num_objects2, result5['mean'], color='yellow')


#plt.plot(num_objects2, result1['mean'], fmt='o-', capsize=5, label='Creation Time', color='blue')
#plt.plot(num_objects2, result2['mean'], fmt='o-', capsize=5, label='Creation Time', color='green')
#plt.plot(num_objects2, result3['mean'], fmt='o-', capsize=5, label='Creation Time', color='red')
#plt.plot(num_objects2, result4['mean'], fmt='o-', capsize=5, label='Creation Time', color='black')
#plt.plot(num_objects2, result5['mean'], fmt='x:', capsize=5, label='Creation Time', color='yellow')


plt.xlabel('(NUM_Object)')
plt.ylabel('Time (Mean and StdDev)')
plt.show()
