PRAGMA foreign_keys = ON;

-- ================= ENUM (CHECK) =================

-- dùng CHECK inline nên không cần create riêng


-- ================= USERS =================
CREATE TABLE IF NOT EXISTS migrations (
  id TEXT PRIMARY KEY,
  executed_at TEXT
);

CREATE TABLE users (
  id TEXT PRIMARY KEY,
  username TEXT NOT NULL UNIQUE,
  hash_password TEXT NOT NULL,
  is_active INTEGER NOT NULL DEFAULT 1,
  created_by TEXT,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= OWNERS =================

CREATE TABLE owners (
  id TEXT PRIMARY KEY,
  first_name TEXT,
  last_name TEXT NOT NULL,
  gender INTEGER NOT NULL,
  user_id TEXT NOT NULL,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (user_id) REFERENCES users(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= STORES =================

CREATE TABLE stores (
  id TEXT PRIMARY KEY,
  name TEXT NOT NULL,
  name_normalize TEXT NOT NULL UNIQUE,
  description TEXT,
  address TEXT,
  phone TEXT NOT NULL UNIQUE,
  owner_id TEXT,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (owner_id) REFERENCES owners(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= STAFFS =================

CREATE TABLE staffs (
  id TEXT PRIMARY KEY,
  first_name TEXT,
  last_name TEXT NOT NULL,
  gender INTEGER NOT NULL,
  user_id TEXT NOT NULL,
  store_id TEXT,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (user_id) REFERENCES users(id),
  FOREIGN KEY (store_id) REFERENCES stores(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= CUSTOMERS =================

CREATE TABLE customers (
  id TEXT PRIMARY KEY,
  fullname TEXT,
  phone TEXT UNIQUE,
  gender INTEGER,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= PRODUCTS =================

CREATE TABLE products (
  id TEXT PRIMARY KEY,
  name TEXT NOT NULL,
  name_normalized TEXT NOT NULL UNIQUE,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= ORDERS =================

CREATE TABLE orders (
  id TEXT PRIMARY KEY,
  seller_id TEXT,
  customer_id TEXT,
  subtotal REAL NOT NULL,
  discount_amount REAL DEFAULT 0,
  total REAL NOT NULL,
  points_earned INTEGER DEFAULT 0,
  points_redeemed INTEGER DEFAULT 0,
  payment_method TEXT NOT NULL DEFAULT 'CASH'
    CHECK (payment_method IN ('CASH','QRCODE','BANK_TRANSFER','OTHER')),
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (seller_id) REFERENCES staffs(id),
  FOREIGN KEY (customer_id) REFERENCES customers(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= ORDER ITEMS =================

CREATE TABLE order_items (
  id TEXT PRIMARY KEY,
  name TEXT,
  product_id TEXT,
  amount REAL NOT NULL DEFAULT 0,
  quantity INTEGER NOT NULL DEFAULT 0,
  subtotal REAL NOT NULL DEFAULT 0,
  discount_amount REAL DEFAULT 0,
  total REAL NOT NULL DEFAULT 0,
  order_id TEXT NOT NULL,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (product_id) REFERENCES products(id),
  FOREIGN KEY (order_id) REFERENCES orders(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= PROMOTION CONFIG =================

CREATE TABLE promotion_configs (
  id TEXT PRIMARY KEY,
  type TEXT NOT NULL CHECK (type IN ('DIRECT_DISCOUNT','POINTS_STEP_DISCOUNT')),
  start_date TEXT NOT NULL,
  end_date TEXT,
  reward_value REAL NOT NULL DEFAULT 0,
  reward_unit TEXT NOT NULL DEFAULT 'ABSOLUTE'
    CHECK (reward_unit IN ('ABSOLUTE','PERCENTAGE')),
  created_by TEXT NOT NULL,
  is_apply_all_stores INTEGER DEFAULT 0,
  max_usages INTEGER NOT NULL DEFAULT 1,
  is_active INTEGER DEFAULT 1,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= PROMOTION CONFIG STORES =================

CREATE TABLE promotion_configs_stores (
  store_id TEXT NOT NULL,
  promotion_config_id TEXT NOT NULL,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  PRIMARY KEY (store_id, promotion_config_id),
  FOREIGN KEY (store_id) REFERENCES stores(id),
  FOREIGN KEY (promotion_config_id) REFERENCES promotion_configs(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= POINT CONFIG =================

CREATE TABLE promotion_points_config (
  promotion_config_id TEXT PRIMARY KEY,
  earn_type TEXT NOT NULL CHECK (earn_type IN ('BY_AMOUNT','BY_QUANTITY')),
  amount_per_point REAL,
  quantity_per_point INTEGER,
  points_per_step INTEGER NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  FOREIGN KEY (promotion_config_id) REFERENCES promotion_configs(id)
);

-- ================= CUSTOMER ACCOUNT =================

CREATE TABLE customer_promotion_account (
  id TEXT PRIMARY KEY,
  is_active INTEGER DEFAULT 1,
  points_balance INTEGER NOT NULL DEFAULT 0,
  points_earned_total INTEGER NOT NULL DEFAULT 0,
  points_redeemed_total INTEGER NOT NULL DEFAULT 0,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (id) REFERENCES customers(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= CARDS =================

CREATE TABLE cards (
  id TEXT PRIMARY KEY,
  nfc_id TEXT NOT NULL UNIQUE,
  qr_code TEXT UNIQUE,
  is_active INTEGER DEFAULT 1,
  is_apply_all_stores INTEGER DEFAULT 0,
  customer_promotion_account_id TEXT,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (customer_promotion_account_id) REFERENCES customer_promotion_account(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= CARDS STORES =================

CREATE TABLE cards_stores (
  card_id TEXT NOT NULL,
  store_id TEXT NOT NULL,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  PRIMARY KEY (card_id, store_id),
  FOREIGN KEY (card_id) REFERENCES cards(id),
  FOREIGN KEY (store_id) REFERENCES stores(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= PROMOTIONS =================

CREATE TABLE promotions (
  promotion_config_id TEXT NOT NULL,
  card_id TEXT NOT NULL,
  usages_count INTEGER NOT NULL DEFAULT 0,
  max_usages INTEGER NOT NULL DEFAULT 1,
  is_active INTEGER DEFAULT 1,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  PRIMARY KEY (promotion_config_id, card_id),
  FOREIGN KEY (promotion_config_id) REFERENCES promotion_configs(id),
  FOREIGN KEY (card_id) REFERENCES cards(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= PROMOTION USAGE =================

CREATE TABLE promotion_usage (
  order_id TEXT NOT NULL,
  promotion_config_id TEXT NOT NULL,
  card_id TEXT NOT NULL,
  discount_amount REAL NOT NULL,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  PRIMARY KEY (order_id, promotion_config_id, card_id),
  FOREIGN KEY (order_id) REFERENCES orders(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= POINTS HISTORY =================

CREATE TABLE promotion_points_history (
  id TEXT PRIMARY KEY,
  promotion_config_id TEXT,
  card_id TEXT,
  order_id TEXT NOT NULL,
  type TEXT NOT NULL CHECK (type IN ('EARN','REDEEM')),
  points INTEGER NOT NULL,
  created_by TEXT NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (promotion_config_id) REFERENCES promotion_configs(id),
  FOREIGN KEY (card_id) REFERENCES cards(id),
  FOREIGN KEY (order_id) REFERENCES orders(id),
  FOREIGN KEY (created_by) REFERENCES users(id),
  UNIQUE (order_id, type)
);

-- ================= INDEXES =================

CREATE INDEX idx_orders_customer_id ON orders(customer_id);
CREATE INDEX idx_orders_seller_id ON orders(seller_id);

CREATE INDEX idx_points_history_card_id ON promotion_points_history(card_id);
CREATE INDEX idx_points_history_order_id ON promotion_points_history(order_id);

CREATE INDEX idx_promotion_usage_card_id ON promotion_usage(card_id);