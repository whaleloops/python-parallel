from joblib import Parallel, delayed
import numpy as np
import time
# what are your inputs, and what operation do you want to
# perform on each input. For example...

gb_test = [100,200]

def processInput(a,i):
    print (test)
    return i + i, a + i

def processInput2(a,inp):
    print (gb_test)
    gb_test.append(inp)
    print (gb_test)
    return [(i + i, a + i) for i in inp]

if __name__ == "__main__":
	temp = 10000000
	inputs = range(temp)
	num_cores = 3
	inputs = [range(0,temp//3),range(temp//3,temp//3*2),range(temp//3*2,temp)] # todo

	a = 0
	start = time.clock()
	results = Parallel(n_jobs=num_cores, backend="multiprocessing")(delayed(processInput2)(a,i) for i in inputs)
	#results = Parallel(n_jobs=num_cores, backend="threading")(delayed(processInput)(a,i) for i in inputs)
	#results = [(processInput(a, i)) for i in inputs]
	results = results[0] + results[1] + results[2]
	train, test = zip(*results)
	print (time.clock()-start)
	print (gb_test)


	train =np.array(train)
	print (train)
	test =np.array(test)
	print (test)
