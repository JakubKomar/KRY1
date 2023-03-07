


for x in range(0,25):
    for i in [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23 , 25]:
        for j in range(1,25):
            enc = (i*x+j)%26
            print(i,j)
            if(x ==enc):
                print("je to v piči")
                exit()