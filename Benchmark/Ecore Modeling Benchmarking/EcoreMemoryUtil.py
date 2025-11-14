import time
import subprocess
import csv
import os
import psutil

# Define executable paths
exe_paths = [
    r"C:\MDE4CPP\MDE4CPP\application\bin\App_InventorySystemExample_ecore.exe"
]

csv_filename = "resource_usage_log.csv"

# Define number of instances manually for each run
num_of_instance_list = [2000, 5000, 10000, 20000, 50000, 80000, 100000, 150000, 200000]

# CSV file initialization
if not os.path.exists(csv_filename):
    with open(csv_filename, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Run", "Num_of_Instance", "Memory_use (MB)", "Avg_CPU_usage (%)"])

# Initialize run number
run_number = 1
if os.path.exists(csv_filename):
    with open(csv_filename, mode="r") as file:
        reader = csv.reader(file)
        rows = list(reader)
        if len(rows) > 1:
            last_run = rows[-1][0]
            if last_run.isdigit():
                run_number = int(last_run) + 1

for exe_path in exe_paths:
    # Start the application silently
    process = subprocess.Popen(exe_path, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    pid = process.pid
    
    # Variables for monitoring
    peak_memory = 0
    cpu_samples = []
    
    # Monitor resource usage until the application exits
    while process.poll() is None:
        try:
            proc = psutil.Process(pid)
            
            # Get memory usage in MB
            current_memory = proc.memory_info().rss / (1024 * 1024)
            peak_memory = max(peak_memory, current_memory)
            
            # Get CPU usage with a 1-second interval for stability
            cpu_usage = proc.cpu_percent(interval=1.0)
            cpu_samples.append(cpu_usage)
            
        except psutil.NoSuchProcess:
            break
    
    # Calculate the average CPU usage from all samples
    avg_cpu_usage = sum(cpu_samples) / len(cpu_samples) if cpu_samples else 0
    
    # Get the corresponding Num_of_Instance for this run
    num_of_instance = num_of_instance_list[run_number - 1] if run_number - 1 < len(num_of_instance_list) else "N/A"
    
    # Append results to CSV
    with open(csv_filename, mode="a", newline="") as file:
        writer = csv.writer(file)
        writer.writerow([run_number, num_of_instance, f"{peak_memory:.2f}", f"{avg_cpu_usage:.2f}"])
    
    run_number += 1  # Increment run number for the next execution