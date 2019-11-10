#![type_length_limit="2873418"]

use async_macros::join;
use async_std::sync::Mutex;
use async_std::task;
use std::sync::Arc;
use std::time::Duration;

use rand::random;

async fn maybe_sleep() {
    if random::<bool>() {
        task::sleep(Duration::from_secs(1)).await;
    }
}

fn main() {
    let a = Arc::new(Mutex::new(0u8));
    let a_1 = a.clone();
    let a_2 = a.clone();

    let t1 = async {
        maybe_sleep().await;
        *a_1.lock().await = 1;
    };
    let t2 = async {
        maybe_sleep().await;
        *a_2.lock().await = 2;
    };

    task::block_on(async {
        join!(t1, t2).await;
        println!("{:?}", a.lock().await);
    });
}
