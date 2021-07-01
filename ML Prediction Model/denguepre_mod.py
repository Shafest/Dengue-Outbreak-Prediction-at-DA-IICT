import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

dataframe=pd.read_csv('data1.csv')

X=dataframe.iloc[:,0:6].values
Y=dataframe.iloc[:,6:7].values

from sklearn.model_selection import train_test_split
Z_train,Z_test,W_train,W_test=train_test_split(X,Y,test_size=0.2,random_state = 0)




from sklearn.preprocessing import StandardScaler
re_Z = StandardScaler()
Z_train = re_Z.fit_transform(Z_train)
Z_test = re_Z.transform(Z_test)
re_W = StandardScaler()
W_train = re_W.fit_transform(W_train)


from keras import regularizers
import tensorflow as tf
model=tf.keras.Sequential()
model.add(tf.keras.layers.Dense(units = 4,input_dim = 6,activation='elu',kernel_regularizer=regularizers.l2(0.001)))
model.add(tf.keras.layers.Dense(units = 4,activation='elu',kernel_regularizer=regularizers.l2(0.001)))
model.add(tf.keras.layers.Dense(units = 4,activation='elu',kernel_regularizer=regularizers.l2(0.001)))
model.add(tf.keras.layers.Dense(units = 1,activation='linear'))
model.compile(loss='mean_squared_error',optimizer='adam',metrics=['accuracy'])

model.summary()

model.fit(Z_test,W_test,epochs=1000,batch_size=10)

W_pred = np.ceil(model.predict(Z_test))



plt.plot(W_pred,color = 'red', label = "Predicted NO Of Cases" )
plt.plot(W_test,color = 'blue', label = "Actual NO Of Cases" )
plt.xlabel("Days")
plt.ylabel("NO Of Cases")
plt.legend()
plt.show() 

print("High Temprature")
H=int(input())
a=[]
a.append(H)
print("Low Tempreture")
L=int(input())
a.append(L)
a.append((H-L))
a.append((H+L)/2)
print("Avg Humidity On A Particular Day")
x=int(input())
a.append(x)
print("diff in humidity")
x=int(input())
a.append(x)
test=[]
test.append(a)

test = re_Z.transform(test)

prediction = np.ceil(re_W.inverse_transform(model.predict(test)))

print(prediction)


    