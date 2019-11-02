use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Duration;

use rand::random;

fn maybe_sleep() {
    if random::<bool>() {
        thread::sleep(Duration::from_secs(1));
    }
}

fn main() {
    let a = Arc::new(Mutex::new(0));
    let a_1 = a.clone();
    let a_2 = a.clone();

    let t1 = thread::spawn(move || {
        maybe_sleep();
        *a_1.lock().unwrap() = 1;
    });
    let t2 = thread::spawn(move || {
        maybe_sleep();
        *a_2.lock().unwrap() = 2;
    });

    let _ = t1.join();
    let _ = t2.join();

    println!("{:?}", a.lock().unwrap());

}
