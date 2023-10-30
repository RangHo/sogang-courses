data = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

odd_index_sum = sum(data[::2])
even_index_sum = sum(data[1::2])
average = sum(data) / len(data)

data.insert(0, odd_index_sum)
data.insert(1, even_index_sum)
data.append(average)

print(data)
