CREATE TABLE IF NOT EXISTS promotions (
    id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    name_normalize TEXT NOT NULL,
    description TEXT,
    promotion_type TEXT CHECK(promotion_type IN ('DIRECT_AMOUNT', 'PERCENTAGE_AMOUNT', 'CUM_QUANTITY')),
    promotion_value REAL DEFAULT(0.0) NOT NULL CHECK(promotion_value > 0),
    start_at TEXT NOT NULL,
    end_at TEXT,
    store_id TEXT,
    required_cummulative_quantity INT,
    cummulative_quantity_rule TEXT CHECK(cummulative_quantity_rule IN ('ORDER', 'ORDER_QUANTITY')),
    FOREIGN KEY(store_id) REFERENCES stores(id)
);

-- INSERT INTO promotion (
--     id,
--     name,
--     name_normalize,
--     description,
--     promotion_type,
--     promotion_value,
--     start_at,
--     end_at,
--     store_id,
--     required_cummulative_quantity,
--     cummulative_quantity_rule
-- ) VALUES
-- (
--     'promo_1',
--     'Giảm 20K cho hóa đơn',
--     'giam_20k_cho_hoa_don',
--     'Giảm trực tiếp 20.000 VND cho mỗi hóa đơn',
--     'DIRECT_AMOUNT',
--     20000,
--     '2026-01-01',
--     '2026-12-31',
--     '1',
--     NULL,
--     NULL
-- ),
-- (
--     'promo_2',
--     'Giảm 10% cho đơn hàng',
--     'giam_10_phan_tram',
--     'Khuyến mãi giảm 10% tổng hóa đơn',
--     'PERCENTAGE_AMOUNT',
--     10,
--     '2026-01-01',
--     '2026-12-31',
--     '1',
--     NULL,
--     NULL
-- ),
-- (
--     'promo_3',
--     'Mua 10 ly tặng 1 ly',
--     'mua_10_tang_1',
--     'Khách hàng mua đủ 10 ly cà phê sẽ được tặng 1 ly miễn phí',
--     'CUM_QUANTITY',
--     1,
--     '2026-01-01',
--     NULL,
--     '1',
--     10,
--     'ORDER_QUANTITY'
-- );