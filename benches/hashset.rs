use std::collections::HashSet;

#[derive(Default)]
struct MyRand {
    seed: u64,
}

impl MyRand {
    fn next(&mut self) -> u64 {
        self.seed = self
            .seed
            .overflowing_mul(123456789)
            .0
            .overflowing_add(101112131415)
            .0;
        self.seed
    }

    fn next_key(&mut self) -> [u8; 32] {
        let mut key = [0u8; 32];
        // Fill the 32-byte key with random data using unsafe pointer writes
        let ptr = key.as_mut_ptr() as *mut u64;
        unsafe {
            *ptr.offset(0) = self.next();
            *ptr.offset(1) = self.next();
            *ptr.offset(2) = self.next();
            *ptr.offset(3) = self.next();
        }
        key
    }
}

fn main() {
    let mut rand = MyRand::default();
    let mut hashset = HashSet::with_capacity(10_000_000);

    // Store keys for later lookup
    let mut keys = Vec::with_capacity(10_000_000);

    // Insert phase
    for _ in 0..1_000_000 {
        let key = rand.next_key();
        keys.push(key);
        hashset.insert(key);
    }

    println!("Inserted: {}", hashset.len());

    // Search phase - lookup all inserted keys
    let mut found = 0;
    for key in &keys {
        if hashset.contains(key) {
            found += 1;
        }
    }

    println!("Found: {}", found);
}
