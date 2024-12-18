# Q

## 1

这里不会竞争吗。在`bh->b_count=1;`之后。

```cpp
struct buffer_head * getblk(int dev,int block)
{
 struct buffer_head * tmp, * bh;

repeat:
 if (bh = get_hash_table(dev,block))
  return bh;
 tmp = free_list;
 do {
  if (tmp->b_count)
   continue;
  if (!bh || BADNESS(tmp)<BADNESS(bh)) {
   bh = tmp;
   if (!BADNESS(tmp))
    break;
  }
/* and repeat until we find something good */
 } while ((tmp = tmp->b_next_free) != free_list);
 if (!bh) {
  sleep_on(&buffer_wait);
  goto repeat;
 }
 wait_on_buffer(bh);
 if (bh->b_count)
  goto repeat;
 while (bh->b_dirt) {
  sync_dev(bh->b_dev);
  wait_on_buffer(bh);
  if (bh->b_count)
   goto repeat;
 }
/* NOTE!! While we slept waiting for this block, somebody else might */
/* already have added "this" block to the cache. check it */
 if (find_buffer(dev,block))
  goto repeat;
/* OK, FINALLY we know that this buffer is the only one of it's kind, */
/* and that it's unused (b_count=0), unlocked (b_lock=0), and clean */
 bh->b_count=1;
 bh->b_dirt=0;
 bh->b_uptodate=0;
 remove_from_queues(bh);
 bh->b_dev=dev;
 bh->b_blocknr=block;
 insert_into_queues(bh);
 return bh;
}
```

## 2

如果在 `*p = *current; /* NOTE! this doesn't copy the supervisor stack */`
时发生调度，那么 会 对进程有影响吗。

```cpp
int copy_process(int nr,long ebp,long edi,long esi,long gs,long none,
  long ebx,long ecx,long edx, 
  long fs,long es,long ds,
  long eip,long cs,long eflags,long esp,long ss)
{
 struct task_struct *p;
 int i;
 struct file *f;

 p = (struct task_struct *) get_free_page();
 if (!p)
  return -EAGAIN;
 task[nr] = p;
 *p = *current; /* NOTE! this doesn't copy the supervisor stack */
 p->state = TASK_UNINTERRUPTIBLE;
```
