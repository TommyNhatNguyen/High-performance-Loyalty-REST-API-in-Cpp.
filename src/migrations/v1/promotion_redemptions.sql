CREATE TABLE IF NOT EXISTS promotion_redemptions (
    promotion_id TEXT NOT NULL,
    customer_id TEXT NOT NULL,
    order_id TEXT NOT NULL,
    FOREIGN KEY (promotion_id, customer_id) REFERENCES promotion_customer(promotion_id, customer_id)
    FOREIGN KEY order_id REFERENCES orders(id)
    PRIMARY KEY (promotion_id, customer_id, order_id)
);

