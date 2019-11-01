import json
#import numpy as np
import matplotlib.pyplot as plt

f =open("../configs/rd53a_test.json", "r")
json_data =json.load(f)
Reg_list = ["GrobalRegister", "PixelRegister"]
mask_col = []
mask_row = []

for colnum in range(len(json_data["PixelRegister"]["column"])):
    for rownum in range(len(json_data["PixelRegister"]["column"]["Hitbus"])):
        mask_col.append(colnum)
        mask_row.append(rownum)

fig = plt.figure()
ax = fig.add_subplot(111)

H = ax.hist2d(colnum, rownum, bins=[400,200])
fig.colorbar(H[3], ax=ax)
plt.show()
