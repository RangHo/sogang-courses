old_list = [[1, 2], [3, 4], [5, 6], [7, 8]]
new_list = []

element1 = []
element1.append(old_list[0][0] + old_list[0][1])
element1.append(old_list[0][0] * old_list[0][1])
new_list.append(element1)

element2 = []
element2.append(old_list[1][0] + old_list[1][1])
element2.append(old_list[1][0] * old_list[1][1])
new_list.append(element2)

element3 = []
element3.append(old_list[2][0] + old_list[2][1])
element3.append(old_list[2][0] * old_list[2][1])
new_list.append(element3)

element4 = []
element4.append(old_list[3][0] + old_list[3][1])
element4.append(old_list[3][0] * old_list[3][1])
new_list.append(element4)

print(new_list)
