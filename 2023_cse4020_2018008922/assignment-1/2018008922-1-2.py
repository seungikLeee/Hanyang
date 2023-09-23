import numpy as np

m = np.array([i for i in range(2,27)])
print('A.')
print(m)
print('')

m = m.reshape((5,5))
print('B.')
print(m)
print('')

m[:, 0] = 0
print('C.')
print(m)
print('')

m = m@m
print('D.')
print(m)
print('')

result = np.sqrt(sum(m[0, :]**2))
print('E.')
print(result)
print('')


