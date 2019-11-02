package example
import scala.util.Random
import scala.concurrent.Future
object Unsafe extends App {
  implicit val ec: scala.concurrent.ExecutionContext = scala.concurrent.ExecutionContext.global
  var a: Int = 0;
  def maybeSlowAssignment(v: Int): Future[Unit] = Future {
    if(Random.nextBoolean){
      Thread.sleep(1000)
    }
    a = v;
  }
  val f1 = maybeSlowAssignment(1)
  val f2 = maybeSlowAssignment(2)
  f1.onComplete { case _ =>
    f2.onComplete { case _ =>
      println(a)
    }
  }
}
