# Pizza Restaurant System

A C++ console application built as an OOP theory project. It simulates a pizza shop's order management system using core object-oriented principles: encapsulation, inheritance, linked lists, and queues.

## Features

- **Menu management** — menu items stored in a custom linked list (`MenuItem`), with add/edit support.
- **Order handling** — customers can add multiple items and quantities to an `Order`, with total cost calculation.
- **Customer records** — base `Customer` class storing name, address, and phone number.
- **Premium customers** — `PremiumCustomer` inherits from `Customer` and adds discount rates and reward points.
- **Order queue** — orders are processed in FIFO order using a custom linked-list-based queue (`enqueueOrder` / `dequeueOrder`).
- **File output** — final order cost and reward points are written to `order_receipt.txt`.

## Tech / Concepts Used

- Classes & objects
- Inheritance (`Customer` → `PremiumCustomer`)
- Linked lists (menu items, order queue)
- File I/O (`fstream`)
- Encapsulation (private customer fields with public getters/setters)

## How to Compile & Run

```bash
g++ main.cpp -o pizzashop
./pizzashop
```

On Windows (MinGW):
```bash
g++ main.cpp -o pizzashop.exe
pizzashop.exe
```

## Sample Flow

1. The shop displays its menu (10 pizzas with prices).
2. The user selects items and quantities to build an order.
3. The user enters customer details.
4. The order total is calculated, a 10% premium discount is applied, and reward points are earned.
5. The receipt is written to `order_receipt.txt`.
6. The order is processed from the queue and displayed with its total.

## Project Structure

```
pizza-restaurant-system-PF-cpp/
├── main.cpp
├── PF_Project_Pizza_Management_System.cpp
└── README.md
```

## Author

OOP Theory Project — Pizza Management System
