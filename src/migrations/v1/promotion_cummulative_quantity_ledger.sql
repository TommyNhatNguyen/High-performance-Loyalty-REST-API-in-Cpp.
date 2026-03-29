CREATE TABLE IF NOT EXISTS promotion_cummulative_quantity_ledger (
    promotion_id TEXT NOT NULL,
    customer_id TEXT NOT NULL,
    order_id TEXT NOT NULL,
    type TEXT CHECK(type IN ('EARN', 'USED')),
    quantity INT CHECK(quantity >= 0),
    FOREIGN KEY (promotion_id, customer_id) REFERENCES promotion_customer(promotion_id, customer_id),
    PRIMARY KEY (promotion_id, customer_id, order_id)
);