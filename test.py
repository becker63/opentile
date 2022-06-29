
# Python3 program to find Closest number in a list
import numpy as np
def closest(lst, K):
      
     lst = np.asarray(lst)
     idx = (np.abs(lst - K)).argmin()
     return lst[idx]
      
# Driver code
lst = [1800, 2000, 240, 805, 1006]
K = 1280
print(closest(lst, K))