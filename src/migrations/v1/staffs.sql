CREATE TABLE IF NOT EXISTS staffs (
    id TEXT PRIMARY KEY,
    username TEXT UNIQUE NOT NULL,
    hash_password TEXT NOT NULL,
    first_name TEXT,
    last_name TEXT,
    phone TEXT NOT NULL,
    gender BOOLEAN NOT NULL DEFAULT(0),
    store_id TEXT NOT NULL,
    FOREIGN KEY(store_id) REFERENCES stores(id)
);

-- INSERT INTO staffs (
--     id,
--     username,
--     hash_password,
--     first_name,
--     last_name,
--     phone,
--     gender,
--     store_id
-- ) VALUES 
-- (
--     'staff_1',
--     'nhat.admin',
--     'hashed_password_123',
--     'Anh',
--     'Nguyen',
--     '0909123456',
--     1,
--     '1'
-- ),
-- (
--     'staff_2',
--     'linh.staff',
--     'hashed_password_456',
--     'Linh',
--     'Tran',
--     '0912345678',
--     0,
--     '1'
-- ),
-- (
--     'staff_3',
--     'test.staff',
--     'hashed_password_456',
--     'Linh',
--     'Tran',
--     '0912345678',
--     0,
--     '2'
-- );