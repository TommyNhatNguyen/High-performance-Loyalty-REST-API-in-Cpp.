PRAGMA foreign_keys = ON;

-- ================= MIGRATIONS =================
CREATE TABLE IF NOT EXISTS migrations (
  id TEXT PRIMARY KEY,
  executed_at TEXT
);

-- ================= USERS =================
CREATE TABLE users (
  id INTEGER PRIMARY KEY,
  username TEXT NOT NULL UNIQUE,
  hash_password TEXT NOT NULL,
  is_active INTEGER NOT NULL DEFAULT 1,
  created_by INTEGER,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= OWNERS =================
CREATE TABLE owners (
  id INTEGER PRIMARY KEY,
  first_name TEXT,
  last_name TEXT NOT NULL,
  gender INTEGER NOT NULL,
  user_id INTEGER NOT NULL,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (user_id) REFERENCES users(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= STORES =================
CREATE TABLE stores (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  name_normalize TEXT NOT NULL UNIQUE,
  description TEXT,
  address TEXT,
  phone TEXT NOT NULL UNIQUE,
  owner_id INTEGER,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (owner_id) REFERENCES owners(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= STAFFS =================
CREATE TABLE staffs (
  id INTEGER PRIMARY KEY,
  first_name TEXT,
  last_name TEXT NOT NULL,
  gender INTEGER NOT NULL,
  user_id INTEGER NOT NULL,
  store_id INTEGER,
  created_by INTEGER NOT NULL,
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
  id INTEGER PRIMARY KEY,
  fullname TEXT,
  phone TEXT UNIQUE,
  gender INTEGER,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= PRODUCTS =================
CREATE TABLE products (
  id INTEGER PRIMARY KEY,
  name TEXT NOT NULL,
  name_normalized TEXT NOT NULL UNIQUE,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= ORDERS =================
CREATE TABLE orders (
  id INTEGER PRIMARY KEY,
  seller_id INTEGER,
  customer_id INTEGER,
  subtotal REAL NOT NULL,
  discount_amount REAL DEFAULT 0,
  total REAL NOT NULL,
  points_earned INTEGER DEFAULT 0,
  points_redeemed INTEGER DEFAULT 0,
  payment_method TEXT NOT NULL DEFAULT 'CASH',
  created_by INTEGER NOT NULL,
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
  id INTEGER PRIMARY KEY,
  order_id INTEGER NOT NULL,
  product_id INTEGER,
  name TEXT,
  amount REAL NOT NULL DEFAULT 0,
  quantity INTEGER NOT NULL DEFAULT 0,
  subtotal REAL NOT NULL DEFAULT 0,
  discount_amount REAL DEFAULT 0,
  total REAL NOT NULL DEFAULT 0,
  created_by INTEGER NOT NULL,
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
  id INTEGER PRIMARY KEY,
  type TEXT NOT NULL CHECK (type IN ('DIRECT_DISCOUNT','POINTS_STEP_DISCOUNT')),
  start_date TEXT NOT NULL,
  end_date TEXT,
  reward_value REAL NOT NULL DEFAULT 0,
  reward_unit TEXT NOT NULL DEFAULT 'ABSOLUTE'
    CHECK (reward_unit IN ('ABSOLUTE','PERCENTAGE')),
  created_by INTEGER NOT NULL,
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
  store_id INTEGER NOT NULL,
  promotion_config_id INTEGER NOT NULL,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  PRIMARY KEY (store_id, promotion_config_id),
  FOREIGN KEY (store_id) REFERENCES stores(id),
  FOREIGN KEY (promotion_config_id) REFERENCES promotion_configs(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= POINT CONFIG =================
CREATE TABLE promotion_points_config (
  promotion_config_id INTEGER PRIMARY KEY,
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
  id INTEGER PRIMARY KEY,
  customer_id INTEGER UNIQUE,
  is_active INTEGER DEFAULT 1,
  points_balance INTEGER NOT NULL DEFAULT 0,
  points_earned_total INTEGER NOT NULL DEFAULT 0,
  points_redeemed_total INTEGER NOT NULL DEFAULT 0,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (customer_id) REFERENCES customers(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= CARDS =================
CREATE TABLE cards (
  id INTEGER PRIMARY KEY,
  nfc_id TEXT NOT NULL UNIQUE,
  is_active INTEGER DEFAULT 1,
  qr_code TEXT,
  is_apply_all_stores INTEGER DEFAULT 0,
  customer_promotion_account_id INTEGER,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  updated_at TEXT,
  deleted_at TEXT,
  deleted INTEGER NOT NULL DEFAULT 0,
  FOREIGN KEY (customer_promotion_account_id) REFERENCES customer_promotion_account(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= CARDS STORES =================
CREATE TABLE cards_stores (
  card_id INTEGER NOT NULL,
  store_id INTEGER NOT NULL,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  PRIMARY KEY (card_id, store_id),
  FOREIGN KEY (card_id) REFERENCES cards(id),
  FOREIGN KEY (store_id) REFERENCES stores(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= PROMOTIONS =================
CREATE TABLE promotions (
  promotion_config_id INTEGER NOT NULL,
  card_id INTEGER NOT NULL,
  usages_count INTEGER NOT NULL DEFAULT 0,
  max_usages INTEGER NOT NULL DEFAULT 1,
  is_active INTEGER DEFAULT 1,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  PRIMARY KEY (promotion_config_id, card_id),
  FOREIGN KEY (promotion_config_id) REFERENCES promotion_configs(id),
  FOREIGN KEY (card_id) REFERENCES cards(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= PROMOTION USAGE =================
CREATE TABLE promotion_usage (
  order_id INTEGER NOT NULL,
  promotion_config_id INTEGER NOT NULL,
  card_id INTEGER NOT NULL,
  discount_amount REAL NOT NULL,
  created_by INTEGER NOT NULL,
  created_at TEXT,
  PRIMARY KEY (order_id, promotion_config_id, card_id),
  FOREIGN KEY (order_id) REFERENCES orders(id),
  FOREIGN KEY (created_by) REFERENCES users(id)
);

-- ================= POINTS HISTORY =================
CREATE TABLE promotion_points_history (
  id INTEGER PRIMARY KEY,
  promotion_config_id INTEGER,
  card_id INTEGER,
  order_id INTEGER NOT NULL,
  type TEXT NOT NULL CHECK (type IN ('EARN','REDEEM')),
  points INTEGER NOT NULL,
  created_by INTEGER NOT NULL,
  created_at TEXT,
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