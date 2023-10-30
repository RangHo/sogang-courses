import math

data = input("Enter data : \n").split()

# Calculate E(X^2) and E(X)^2
expected_sq_x = 0
sq_expected_x = 0
for value in data:
    expected_sq_x += float(value)**2
    sq_expected_x += float(value)
expected_sq_x = expected_sq_x / len(data)
sq_expected_x = (sq_expected_x / len(data))**2

sigma = math.sqrt(expected_sq_x - sq_expected_x)

print("Standard deviation = {:.5f}".format(sigma))
