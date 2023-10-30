airports = ['ICN', 'KIX', 'CDG', 'LIS']

result = ""

for i in range(len(airports)):
    if i == len(airports) - 1:
        result += airports[i]
    else:
        result = result + airports[i] + "->"

print(result)
