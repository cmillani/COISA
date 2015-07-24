import matplotlib
import subprocess

p = subprocess.Popen(['arch'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
arch, err = p.communicate()
arch = arch.strip('\r\n')
subprocess.call(['mkdir', 'tests/'+arch])
print "Plotting all data into " + arch 