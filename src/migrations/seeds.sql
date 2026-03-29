-- ================= USERS =================
INSERT INTO users (id, username, hash_password, created_at) VALUES
('u1', 'admin', 'x', datetime('now')),
('u2', 'staff1', 'x', datetime('now')),
('u3', 'staff2', 'x', datetime('now'));

-- ================= OWNERS =================
INSERT INTO owners (id, last_name, gender, user_id, created_by, created_at) VALUES
('o1', 'Nguyen', 1, 'u1', 'u1', datetime('now'));

-- ================= STORES =================
INSERT INTO stores (id, name, name_normalize, phone, owner_id, created_by, created_at) VALUES
('s1', 'Coffee A', 'coffee_a', '0900000001', 'o1', 'u1', datetime('now')),
('s2', 'Coffee B', 'coffee_b', '0900000002', 'o1', 'u1', datetime('now'));

-- ================= STAFF =================
INSERT INTO staffs (id, last_name, gender, user_id, store_id, created_by, created_at) VALUES
('st1', 'Staff A', 1, 'u2', 's1', 'u1', datetime('now')),
('st2', 'Staff B', 1, 'u3', 's2', 'u1', datetime('now'));

-- ================= CUSTOMERS =================
INSERT INTO customers (id, fullname, phone, created_by, created_at) VALUES
('c1', 'Customer A', '0911111111', 'u1', datetime('now')),
('c2', 'Customer B', '0922222222', 'u1', datetime('now'));

-- ================= CUSTOMER ACCOUNT =================
INSERT INTO customer_promotion_account (
  id, points_balance, points_earned_total, points_redeemed_total, created_by, created_at
) VALUES
('c1', 0, 0, 0, 'u1', datetime('now')),
('c2', 20, 20, 0, 'u1', datetime('now')); -- c2 có sẵn điểm

-- ================= CARDS =================
INSERT INTO cards (id, nfc_id, qr_code, customer_promotion_account_id, created_by, created_at) VALUES
('card1', 'nfc1', 'qr1', 'c1', 'u1', datetime('now')),
('card2', 'nfc2', 'qr2', 'c2', 'u1', datetime('now'));

-- ================= PRODUCTS =================
INSERT INTO products (id, name, name_normalized, created_by, created_at) VALUES
('p1', 'Coffee', 'coffee', 'u1', datetime('now')),
('p2', 'Milk Tea', 'milk_tea', 'u1', datetime('now'));

-- =====================================================
-- 🔥 PROMOTION 1: POINTS BY AMOUNT
-- =====================================================
-- 10k = 1 point, 10 points = 5k discount

INSERT INTO promotion_configs (
  id, type, start_date, reward_value, reward_unit, created_by, is_active, created_at
) VALUES
('promo_amount', 'POINTS_STEP_DISCOUNT', date('now'), 5000, 'ABSOLUTE', 'u1', 1, datetime('now'));

INSERT INTO promotion_points_config (
  promotion_config_id, earn_type, amount_per_point, points_per_step, created_at
) VALUES
('promo_amount', 'BY_AMOUNT', 10000, 10, datetime('now'));

-- =====================================================
-- 🔥 PROMOTION 2: POINTS BY QUANTITY
-- =====================================================
-- 2 items = 1 point, 5 points = 10% discount

INSERT INTO promotion_configs (
  id, type, start_date, reward_value, reward_unit, created_by, is_active, created_at
) VALUES
('promo_quantity', 'POINTS_STEP_DISCOUNT', date('now'), 10, 'PERCENTAGE', 'u1', 1, datetime('now'));

INSERT INTO promotion_points_config (
  promotion_config_id, earn_type, quantity_per_point, points_per_step, created_at
) VALUES
('promo_quantity', 'BY_QUANTITY', 2, 5, datetime('now'));

-- =====================================================
-- 🔥 PROMOTION ASSIGN
-- =====================================================
INSERT INTO promotions (promotion_config_id, card_id, max_usages, created_by, created_at) VALUES
('promo_amount', 'card1', 999, 'u1', datetime('now')),
('promo_quantity', 'card1', 999, 'u1', datetime('now')),
('promo_amount', 'card2', 1, 'u1', datetime('now')); -- giới hạn usage

-- =====================================================
-- 🧾 CASE 1: ORDER earn points (amount)
-- =====================================================
INSERT INTO orders (id, seller_id, customer_id, subtotal, total, created_by, created_at) VALUES
('order1', 'st1', 'c1', 50000, 50000, 'u1', datetime('now'));

INSERT INTO order_items (id, product_id, amount, quantity, subtotal, total, order_id, created_by, created_at) VALUES
('oi1', 'p1', 25000, 2, 50000, 50000, 'order1', 'u1', datetime('now'));

-- earn 5 points
INSERT INTO promotion_points_history VALUES
('ph1', 'promo_amount', 'card1', 'order1', 'EARN', 5, 'u1', datetime('now'), NULL, NULL, 0);

-- =====================================================
-- 🧾 CASE 2: ORDER đủ điểm → redeem
-- =====================================================
INSERT INTO orders (id, seller_id, customer_id, subtotal, discount_amount, total, created_by, created_at) VALUES
('order2', 'st1', 'c2', 100000, 5000, 95000, 'u1', datetime('now'));

-- redeem 10 points
INSERT INTO promotion_points_history VALUES
('ph2', 'promo_amount', 'card2', 'order2', 'REDEEM', 10, 'u1', datetime('now'), NULL, NULL, 0);

UPDATE customer_promotion_account
SET points_balance = points_balance - 10,
    points_redeemed_total = points_redeemed_total + 10
WHERE id = 'c2';

-- =====================================================
-- 🧾 CASE 3: QUANTITY earn
-- =====================================================
INSERT INTO orders (id, seller_id, customer_id, subtotal, total, created_by, created_at) VALUES
('order3', 'st1', 'c1', 60000, 60000, 'u1', datetime('now'));

INSERT INTO order_items (id, product_id, amount, quantity, subtotal, total, order_id, created_by, created_at) VALUES
('oi3', 'p2', 20000, 3, 60000, 60000, 'order3', 'u1', datetime('now'));

-- 3 items → 1 point
INSERT INTO promotion_points_history VALUES
('ph3', 'promo_quantity', 'card1', 'order3', 'EARN', 1, 'u1', datetime('now'), NULL, NULL, 0);

-- =====================================================
-- 🧾 CASE 4: MULTI PROMOTION APPLY
-- =====================================================
INSERT INTO orders (id, seller_id, customer_id, subtotal, discount_amount, total, created_by, created_at) VALUES
('order4', 'st1', 'c1', 100000, 15000, 85000, 'u1', datetime('now'));

-- usage record
INSERT INTO promotion_usage VALUES
('order4', 'promo_amount', 'card1', 5000, 'u1', datetime('now'), NULL, NULL, 0),
('order4', 'promo_quantity', 'card1', 10000, 'u1', datetime('now'), NULL, NULL, 0);

-- =====================================================
-- 🧾 CASE 5: usage limit reached
-- =====================================================
-- INSERT INTO promotions (promotion_config_id, card_id, usages_count, max_usages, created_by, created_at)
-- VALUES ('promo_amount', 'card2', 1, 1, 'u1', datetime('now'));

-- =====================================================
-- 🧾 CASE 6: expired promotion
-- =====================================================
INSERT INTO promotion_configs (
  id, type, start_date, end_date, reward_value, reward_unit, created_by, is_active, created_at
) VALUES
('promo_expired', 'DIRECT_DISCOUNT', date('now','-10 days'), date('now','-1 day'), 10000, 'ABSOLUTE', 'u1', 1, datetime('now'));