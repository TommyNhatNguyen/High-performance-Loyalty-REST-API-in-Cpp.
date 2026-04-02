-- ================= USERS =================
INSERT INTO users (username, hash_password, created_at) VALUES
('admin', 'x', datetime('now')),
('staff1', 'x', datetime('now')),
('staff2', 'x', datetime('now'));

-- ================= OWNERS =================
INSERT INTO owners (last_name, gender, user_id, created_by, created_at) VALUES
('Nguyen', 1, 1, 1, datetime('now'));

-- ================= STORES =================
INSERT INTO stores (name, name_normalize, phone, owner_id, created_by, created_at) VALUES
('Coffee A', 'coffee_a', '0900000001', 1, 1, datetime('now')),
('Coffee B', 'coffee_b', '0900000002', 1, 1, datetime('now'));

-- ================= STAFF =================
INSERT INTO staffs (last_name, gender, user_id, store_id, created_by, created_at) VALUES
('Staff A', 1, 2, 1, 1, datetime('now')),
('Staff B', 1, 3, 2, 1, datetime('now'));

-- ================= CUSTOMERS =================
INSERT INTO customers (fullname, phone, created_by, created_at) VALUES
('Customer A', '0911111111', 1, datetime('now')),
('Customer B', '0922222222', 1, datetime('now'));

-- ================= CUSTOMER ACCOUNT =================
INSERT INTO customer_promotion_account (
  customer_id, points_balance, points_earned_total, points_redeemed_total, created_by, created_at
) VALUES
(1, 0, 0, 0, 1, datetime('now')),
(2, 20, 20, 0, 1, datetime('now'));

-- ================= CARDS =================
INSERT INTO cards (nfc_id, qr_code, customer_promotion_account_id, created_by, created_at) VALUES
('nfc1', 'qr1', 1, 1, datetime('now')),
('nfc2', 'qr2', 2, 1, datetime('now'));

-- ================= PRODUCTS =================
INSERT INTO products (name, name_normalized, created_by, created_at) VALUES
('Coffee', 'coffee', 1, datetime('now')),
('Milk Tea', 'milk_tea', 1, datetime('now'));

-- =====================================================
-- 🔥 PROMOTION 1: POINTS BY AMOUNT
-- =====================================================
INSERT INTO promotion_configs (
  type, start_date, reward_value, reward_unit, created_by, is_active, created_at
) VALUES
('POINTS_STEP_DISCOUNT', date('now'), 5000, 'ABSOLUTE', 1, 1, datetime('now'));

INSERT INTO promotion_points_config (
  promotion_config_id, earn_type, amount_per_point, points_per_step, created_at
) VALUES
(1, 'BY_AMOUNT', 10000, 10, datetime('now'));

-- =====================================================
-- 🔥 PROMOTION 2: POINTS BY QUANTITY
-- =====================================================
INSERT INTO promotion_configs (
  type, start_date, reward_value, reward_unit, created_by, is_active, created_at
) VALUES
('POINTS_STEP_DISCOUNT', date('now'), 10, 'PERCENTAGE', 1, 1, datetime('now'));

INSERT INTO promotion_points_config (
  promotion_config_id, earn_type, quantity_per_point, points_per_step, created_at
) VALUES
(2, 'BY_QUANTITY', 2, 5, datetime('now'));

-- =====================================================
-- 🔥 PROMOTION ASSIGN
-- =====================================================
INSERT INTO promotions (promotion_config_id, card_id, max_usages, created_by, created_at) VALUES
(1, 1, 999, 1, datetime('now')),
(2, 1, 999, 1, datetime('now')),
(1, 2, 1, 1, datetime('now'));

-- =====================================================
-- 🧾 CASE 1: ORDER earn points (amount)
-- =====================================================
INSERT INTO orders (seller_id, customer_id, subtotal, total, created_by, created_at) VALUES
(1, 1, 50000, 50000, 1, datetime('now'));

INSERT INTO order_items (order_id, product_id, amount, quantity, subtotal, total, created_by, created_at) VALUES
(1, 1, 25000, 2, 50000, 50000, 1, datetime('now'));

INSERT INTO promotion_points_history (
  promotion_config_id, card_id, order_id, type, points, created_by, created_at
) VALUES
(1, 1, 1, 'EARN', 5, 1, datetime('now'));

-- =====================================================
-- 🧾 CASE 2: redeem
-- =====================================================
INSERT INTO orders (seller_id, customer_id, subtotal, discount_amount, total, created_by, created_at) VALUES
(1, 2, 100000, 5000, 95000, 1, datetime('now'));

INSERT INTO promotion_points_history (
  promotion_config_id, card_id, order_id, type, points, created_by, created_at
) VALUES
(1, 2, 2, 'REDEEM', 10, 1, datetime('now'));

UPDATE customer_promotion_account
SET points_balance = points_balance - 10,
    points_redeemed_total = points_redeemed_total + 10
WHERE customer_id = 2;

-- =====================================================
-- 🧾 CASE 3: QUANTITY earn
-- =====================================================
INSERT INTO orders (seller_id, customer_id, subtotal, total, created_by, created_at) VALUES
(1, 1, 60000, 60000, 1, datetime('now'));

INSERT INTO order_items (order_id, product_id, amount, quantity, subtotal, total, created_by, created_at) VALUES
(3, 2, 20000, 3, 60000, 60000, 1, datetime('now'));

INSERT INTO promotion_points_history (
  promotion_config_id, card_id, order_id, type, points, created_by, created_at
) VALUES
(2, 1, 3, 'EARN', 1, 1, datetime('now'));

-- =====================================================
-- 🧾 CASE 4: MULTI PROMOTION
-- =====================================================
INSERT INTO orders (seller_id, customer_id, subtotal, discount_amount, total, created_by, created_at) VALUES
(1, 1, 100000, 15000, 85000, 1, datetime('now'));

INSERT INTO promotion_usage (
  order_id, promotion_config_id, card_id, discount_amount, created_by, created_at
) VALUES
(4, 1, 1, 5000, 1, datetime('now')),
(4, 2, 1, 10000, 1, datetime('now'));

-- =====================================================
-- 🧾 CASE 6: expired promotion
-- =====================================================
INSERT INTO promotion_configs (
  type, start_date, end_date, reward_value, reward_unit, created_by, is_active, created_at
) VALUES
('DIRECT_DISCOUNT', date('now','-10 days'), date('now','-1 day'), 10000, 'ABSOLUTE', 1, 1, datetime('now'));