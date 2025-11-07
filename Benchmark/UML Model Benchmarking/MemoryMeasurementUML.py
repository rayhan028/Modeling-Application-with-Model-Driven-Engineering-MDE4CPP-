import psutil
import time
import subprocess

exe_path = r"C:\MDE4CPP\MDE4CPP\application\bin\App_ClinicModel.exe" # absolute path to the .exe

#  process begin
process = subprocess.Popen(exe_path)
pid = process.pid
peak_memory = 0 # initialize memory counter 

# #tracking peak memory until process completes
while process.poll() is None:
    try:
        proc = psutil.Process(pid)
        current_memory = proc.memory_info().rss / (1024 * 1024)  # MB
        peak_memory = max(peak_memory, current_memory)
    except:
        break
    time.sleep(0.1)

# show peak memory value after process is done
print(f"\nPeak Memory Usage: {peak_memory:.2f} MB")