# threading-market-checkout

The project simulates supermarket checkout lines (queues). The main program first reads a product information file, ProductPrice.xml, which contains all products and their names, barcodes, and prices, and stores the product details in a database. It then creates a queue manager which reads a list of carts and the products (identified by barcodes) in each cart in a CSV file, Carts.csv (1000 carts), and builds a queue of carts to distribute to multiple checkout lines (queues) to process. 

The queue manager spawns multiple threads for each thread to run one checkout queue, and then the queue manager goes through the list of carts (waiting to be checkout) and distributes the first cart in line to a checkout queue which has the minimum number of waiting carts in the queue. 

When a cart reaches the front of the queue, it processes one product at a time by spawning a thread to send a single product barcode to the database to retrieve the product's name and price. Although there are multiple checkout queues, and each cart at the front of each queue sends a product barcode by a spawning thread to the database simultaneously, the product database can only be accessed by one product at a time, using thread blocking and unblocking synchronization techniques. 

When the queue finishes processing a cart, it will write out a receipt file with all the products' names and prices, and also the total price in the cart. The queue manager continues the distribution until it runs out of the carts. All queue threads will be joined by the queue manager at the end when they finish processing all carts in the queues.

## Architecture
The main program uses a FileIO class object to read a product information file and store the data in a DataBase class object. Then it uses a QueueManager to read a CSV file with a list of carts and their products in each cart, and to store the carts to distribute to checkout queues later (Queue objects). The QueueManager creates a list of Queue class objects (defined in QueueManager.h and QueueManager.cpp) and C++ thread class objects to run the Queue objects' run function. 

Each Queue object acts like a checkout line (queue), and it adds more carts to its queue (a C++ deque object) by creating Cart class objects, when QueueManager dispatches more carts to it. The Cart objects' processing function spawns a C++ thread to run the DataBase object's get_product_info function one product at a time. The product DataBase object can only be accessed by one product at a time, using thread blocking and unblocking synchronization techniques.  Thread blocking and unblocking synchronization techniques are also used between QueueManager object and all Queue objects. 

![image](https://github.com/carab9/threading-market-checkout/blob/main/market_checkout.jpg?raw=true)

## Requirements

C++ and C++ libraries: iostream, fstream, vector, tuple, map, algorithm, iterator, regex, mutex, condition_variable, thread, chrono, smart pointers

## Technical Skills

C++ thread for multi-threading, mutex, condition_variable for thread synchronization, queue, regular expressions (to parse ProductPrice.xml and Carts.csv), smart pointers, STL containers such as vector, tuple, map, STL algorithms, and date and time utilities chrono.

## Results

There are 1000 receipt files written out by the queue threads and each is named by <cart name>_<time stamp>.txt

![image](https://github.com/carab9/threading-market-checkout/blob/main/threading_checkout.png?raw=true)
