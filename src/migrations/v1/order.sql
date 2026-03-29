CREATE TABLE IF NOT EXISTS orders (
    id TEXT PRIMARY KEY,
    name TEXT,
    description TEXT,    
    subtotal REAL NOT NULL DEFAULT 0,
    discount_amount REAL NOT NULL DEFAULT 0,
    total REAL NOT NULL,
    quantity INT NOT NULL,
    cashier_id TEXT NOT NULL,
    store_id TEXT NOT NULL,
    customer_id TEXT NOT NULL,
    FOREIGN KEY(cashier_id) REFERENCES staffs(id),
    FOREIGN KEY(store_id) REFERENCES stores(id),
    FOREIGN KEY(customer_id) REFERENCES customers(id)
);