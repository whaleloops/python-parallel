import multiprocessing
import time
import numpy as np

def worker(iden, rows, columns, n_jobs, shared_arr):
    print (shared_arr)
    for i in range(iden, rows, n_jobs):
        shared_arr[i] = iden+1

if __name__ == '__main__':

    n_jobs = 2
    rows = 10
    columns = 7
    temp = np.ctypeslib.as_ctypes(np.zeros((rows,columns)))
    print (temp._type_)
    shared_arr = multiprocessing.Array(temp._type_, temp)
    # shared_arr = multiprocessing.Array('d', rows, lock=False)


    # initialize processes
    processes = [multiprocessing.Process(target=worker, args=(i, rows, columns, n_jobs, shared_arr)) for i in range(n_jobs)]
    # start new processes
    for p in processes:
        p.start()
    # Main process wait for all processes to complete
    for p in processes:
        p.join()

    print (shared_arr)
    print (np.ctypeslib.as_array(shared_arr, shape=None))