import sympy as s
import numpy as np
from math import radians
from contextlib import redirect_stdout

def round2zero(m, e):
    for i in range(m.shape[0]):
        for j in range(m.shape[1]):
            if (isinstance(m[i,j], s.Float) and m[i,j] < e):
                m[i,j] = 0

theta_0, theta_1,theta_2,x,y,z = s.symbols('theta0 theta_1 theta_2 x y z')

dht = np.array([
    [theta_0 - radians(90),   radians(-90),    0,    0],
    [theta_1 + radians(180),   radians(-90),     0,  0],
    [0,      0,      0,     0],
    [theta_2,      0,      0,     0]
])

# a1 = 35
# a2 = 25
# a3 = 20
# a4 = -1
# a5 = -1
# a6 = 27
# a7 = 15
# a8 = 45

# dht = np.array([
#     [180 + theta_1,   radians(90),    -a2,     a1-a3],
#     [theta_2,   radians(0),      -(a6+a7),  0],
#     [radians(90),      radians(0),      -a8,     0]
# ])

# a1 = 0.75
# a2 = 0.825
# dht = s.Matrix([
#     [theta_1,   np.radians(-90),    a1, 0],
#     [theta_2,   np.radians(0),      a2, 0]    
# ])
# print(dht.shape)
# quit()
transformations = []
for line_no in range(dht.shape[0]):    
    theta = dht[line_no, 0]
    alpha = dht[line_no, 1]
    r = dht[line_no, 2]
    d = dht[line_no, 3]
    H = s.Matrix([
        [s.cos(theta), -s.sin(theta)*s.cos(alpha), s.sin(theta)*s.sin(alpha), r*s.cos(theta)],
        [s.sin(theta), s.cos(theta)*s.cos(alpha), -s.cos(theta)*s.sin(alpha), r*s.sin(theta)],
        [0, s.sin(alpha), s.cos(alpha), d],
        [0,  0,  0 ,   1],
    ])
    transformations.append(H)
# print(transformations[0])
# quit()

p = s.Matrix([
    [x], 
    [y],
    [z],
    [1]
])
# p = np.array([ 0, 0, 0, 1 ])

H = transformations[0]
for h in transformations:
    # if(np.array_equal(H,h)):
    if(H.equals(h)):
        continue
    H = H * h        
    # p = np.dot(h, p)
# print(H)
p = H * p


# round2zero(p, .0000001)
# p = s.simplify(p)

p = s.nsimplify(p,tolerance=1e-10,rational=True)
p = s.simplify(p)
p = p.evalf()
# p = s.N(p)
s.init_printing(use_unicode=True)
# s.init_session()

with open('output.txt', 'w') as f:
    with redirect_stdout(f):
        s.pprint(p, wrap_line=False)
