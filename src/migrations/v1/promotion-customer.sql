CREATE TABLE IF NOT EXISTS promotion_customer (
    promotion_id TEXT NOT NULL,
    customer_id TEXT NOT NULL,
    expired_at DATE,
    cummulative_quantity INT,
    PRIMARY KEY (promotion_id, customer_id)
);