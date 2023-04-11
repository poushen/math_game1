import numpy as np

count = 0
# the black cells are filled with 0
grid = [[ 1, 0, 0,12,31],
        [ 0, 0, 0, 0,27],
        [ 0, 0, 0, 0,29],
        [16, 0, 0,10,49],
        [43,37,23,33, 0]]

def possible(y,x,n):
  global grid
  # n is the number we want to fill in

  # 3rd
  # can't repeat
  for j in range(4):
    for i in range(4):
      if grid[j][i] == n:
        return False

  # 1st , check row y
  count = 0
  for i in range(4):
    count += grid[y][i]
  count += n
  if count > grid[y][4]:
    return False
  with_value = True
  for i in range(4):
    if i != x:
      if grid[y][i] == 0:
        with_value = False
  if with_value:
    if count != grid[y][4]:
      return False
  # check row y, if all 4 cell are bigger than 0
  #if grid[y][0] > 0 and grid[y][1] > 0 and grid[y][2] > 0 and grid[y][3] > 0:
  #  if count != grid[y][4]:
  #    return False

  # 2nd, check column x
  count = 0
  for i in range(4):
    count += grid[i][x]
  count += n
  if count > grid[4][x]:
    return False
  with_value = True
  for j in range(4):
    if j != y:
      if grid[j][x] == 0:
        with_value = False
  if with_value:
    if count != grid[4][x]:
        return False
  # check column x, if all 4 cell are bigger than 0
  #if grid[0][x] > 0 and grid[1][x] > 0 and grid[2][x] > 0 and grid[3][x] > 0:
  #  if count != grid[4][x]:
  #    return False

  # return true if pass all 2 checks.
  return True

def solve():
  global grid, count
  for y in range(4):
    for x in range(4):
      # Find blank positions in the grid (value = 0)
      if grid[y][x] == 0:
        # Loop n from 1-16
        for n in range(1,17):
          # print("{},{},{}".format(y,x,n))
          if possible(y,x,n):
            grid[y][x] = n
            solve()

            # This is where backtracking happens
            # Reset the latest position back to 0 and try with new n value
            grid[y][x] = 0
        return
  count = count + 1
  print("id:{}".format(count))
  print(np.matrix(grid))
  #input('More?')

solve()
