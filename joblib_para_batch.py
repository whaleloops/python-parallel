from joblib import Parallel, delayed
from time import sleep, time

def solve_one_task(task):
    # Solves one task at a time
    sleep(5)
    print("%d. Task #%d is being solved"%(time(), task))
    sleep(1)
    return task

def task_gen(max_task):
    current_task = 0
    while current_task < max_task:
        print("%d. Task #%d was dispatched"%(time(), current_task))
        yield current_task
        current_task += 1
if __name__ == '__main__':
    Parallel(n_jobs=2, backend = 'multiprocessing', batch_size=1, pre_dispatch=3)(
            delayed(solve_one_task)(task) for task in task_gen(10))