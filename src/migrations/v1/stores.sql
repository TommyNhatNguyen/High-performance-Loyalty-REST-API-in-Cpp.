CREATE TABLE IF NOT EXISTS stores (
    id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    phone TEXT NOT NULL,
    address TEXT,
    owner_id TEXT NOT NULL,
    FOREIGN KEY (owner_id) REFERENCES owners(id)
);

-- INSERT INTO stores (id, name, phone, address, owner_id)
-- VALUES ('1', 'cua hang ca phe', '09092829909', '1622/52 nguyen thi thap', '1');