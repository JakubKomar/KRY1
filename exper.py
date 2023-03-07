
def n(a):
    return ord(a)-65

vyskyt =     [n('L').n('Z'),n('J'),n('E'),n('V'),n('C'),n('P'),n('N')]
vaha =       [8, 7, 7,6,5,5,5,4,3]
nejcastejsi =[n('E'),n('O'),n('A'),n('I'),n('N'),n('S'),n('T'),n('R'),n('V'),n('D'),n('P'),n('M'),n('U')]
ztrata =     [8, 7, 7,6,5,5,5,4,3,1,1,1,1]

storege={}
counter=0
for mostLeter in range(0,len(vyskyt)):
    for guestLeter in range(0,len(nejcastejsi)):
        for i in [1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23 , 25]:
            for j in range(0,25):
                counter+=1
                if  nejcastejsi[guestLeter] == (i*vyskyt[mostLeter]+j)%26:
                    key=str(i)+","+str(j)
                    if(key in  storege):
                        storege[key]+=8- abs((vaha[mostLeter] -ztrata[guestLeter]))
                    else:
                        storege[key]=8- abs((vaha[mostLeter] -ztrata[guestLeter]))

print(dict(sorted(storege.items(), key=lambda item: item[1])))
print(counter)

8.82,
1.665,
2.6,
3.62,
10.5,
0.394,
0.343,
1.296,
1.007,
7.673,
1.983,
3.752,
4.097,
3.662,
6.73,
8.3,
3.454,
0.006,
5.163,
5.437,
5.59,
3.845,
4.378,
0.072
0.092,
2.7,
3.145
