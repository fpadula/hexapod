import numpy as np
from math import radians, sin,cos

# a1 = 35
# a2 = 27.5
# a3 = 26
# a4 = 22
# a5 = 25
# a6 = 60
# a7 = 15

# dht = np.array([
#     [radians(theta_1),   radians(-90),    a2,     a1],
#     [radians(180+theta_2),   radians(0),      -(a4+a7),  a3-a5],
#     [radians(90),       radians(0),      -a6,     0]
# ])


def get_H(dht_mat):
    transformations = []
    for line in dht_mat:
        theta = line[0]
        alpha = line[1]
        r = line[2]
        d = line[3]
        H = np.array([
            [cos(theta), -sin(theta)*cos(alpha), sin(theta)*sin(alpha), r*cos(theta)],
            [sin(theta), cos(theta)*cos(alpha), -cos(theta)*sin(alpha), r*sin(theta)],
            [0, sin(alpha), cos(alpha), d],
            [0,  0,  0 ,   1],
        ])
        transformations.append(H)    
    H = transformations[0]
    for h in transformations:
        if(np.array_equal(H,h)):
            continue
        H = np.dot(H, h)        
        # p = np.dot(h, p)
    return H





def main():
    theta_1 = 90
    theta_2 = 90
    a1 = 35
    a2 = 25
    a3 = 20
    a4 = -1
    a5 = -1
    a6 = 27
    a7 = 15
    a8 = 45

    dht = np.array([
        [radians(180 + theta_1),    radians(90),    -a2,        (a1-a3)],
        [radians(theta_2),          radians(0),     -(a6+a7),   0],
        [radians(90),               radians(0),     -a8,        0]
    ])

    
    H = get_H(dht)
    p = np.array([
        [0], 
        [0],
        [0],
        [1]
    ])
    p = np.dot(H, p).reshape(1,4)[0][:-1]
    np.set_printoptions(suppress=True)
    print(p)    

if __name__ == "__main__":
    main()