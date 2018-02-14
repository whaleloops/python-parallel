import multiprocessing
import time

def worker(iden, ele, queue):
    name = multiprocessing.current_process().name
    print (name, 'Starting: Hi', ele)
    time.sleep(2)
    print (name, 'Exiting')
    queue.put((iden,ele))

def my_service(iden, ele, queue):
    name = multiprocessing.current_process().name
    print (name, 'Starting: Hi', ele)
    time.sleep(3)
    print (name, 'Exiting')
    queue.put((iden,ele))

if __name__ == '__main__':

    q = multiprocessing.Queue()
    lock = multiprocessing.Lock()

    service = multiprocessing.Process(target=my_service, args=(0, 'bob', q))
    worker_1 = multiprocessing.Process(name='worker 1', target=worker, args=(1, 'david', q))
    worker_2 = multiprocessing.Process(target=worker, args=(2, 'carl', q)) # use default name

    service.start()
    worker_1.start()
    worker_2.start()

    print ("def")

    service.join()
    worker_1.join()
    worker_2.join()

    print ("abc")

    results = [q.get() for p in range(3)]
    results.sort()
    results = [r[1] for r in results]
    print(results)