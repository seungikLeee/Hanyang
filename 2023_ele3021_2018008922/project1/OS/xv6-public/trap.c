#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "traps.h"
#include "spinlock.h"

// Interrupt descriptor table (shared by all CPUs).
struct gatedesc idt[256];
extern uint vectors[];  // in vectors.S: array of 256 entry pointers
struct spinlock tickslock;
uint ticks;

void
tvinit(void)
{
  int i;

  for(i = 0; i < 256; i++)
    SETGATE(idt[i], 0, SEG_KCODE<<3, vectors[i], 0);
  SETGATE(idt[T_SYSCALL], 1, SEG_KCODE<<3, vectors[T_SYSCALL], DPL_USER);
  
  SETGATE(idt[T_USERINT], 1, SEG_KCODE<<3, vectors[T_USERINT], DPL_USER);
  
  SETGATE(idt[T_SCHELOCK], 1, SEG_KCODE<<3, vectors[T_SCHELOCK], DPL_USER);
  
  SETGATE(idt[T_SCHEUNLOCK], 1, SEG_KCODE<<3, vectors[T_SCHEUNLOCK], DPL_USER);
  
  initlock(&tickslock, "time");
}

void
idtinit(void)
{
  lidt(idt, sizeof(idt));
}

//PAGEBREAK: 41
void
trap(struct trapframe *tf)
{
  if(tf->trapno == T_SYSCALL){
    if(myproc()->killed)
      exit();
    myproc()->tf = tf;
    syscall();
    if(myproc()->killed)
      exit();
    return;
  }

  if(tf->trapno == T_USERINT){
    mycall();
    exit();
  }

  if(tf->trapno == T_SCHELOCK){
    if(myproc()->killed)
      exit();
    myproc()->tf = tf;
    schedulerLock(2018008922);
    if(myproc()->killed)
      exit();
    return;
  }

  if(tf->trapno == T_SCHEUNLOCK){
    if(myproc()->killed)
      exit();
    myproc()->tf = tf;
    schedulerUnlock(2018008922);
    if(myproc()->killed)
      exit();
    return;  
  }
 
  switch(tf->trapno){
  case T_IRQ0 + IRQ_TIMER:
    if(cpuid() == 0){
      acquire(&tickslock);
      ticks++;
      
      if(myproc()){
        myproc()->p_tick++;
      }
      
      wakeup(&ticks);
      release(&tickslock);
    }
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE:
    ideintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE+1:
    // Bochs generates spurious IDE1 interrupts.
    break;
  case T_IRQ0 + IRQ_KBD:
    kbdintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_COM1:
    uartintr();
    lapiceoi();
    break;
  case T_IRQ0 + 7:
  case T_IRQ0 + IRQ_SPURIOUS:
    cprintf("cpu%d: spurious interrupt at %x:%x\n",
            cpuid(), tf->cs, tf->eip);
    lapiceoi();
    break;

  //PAGEBREAK: 13
  default:
    if(myproc() == 0 || (tf->cs&3) == 0){
      // In kernel, it must be our mistake.
      cprintf("unexpected trap %d from cpu %d eip %x (cr2=0x%x)\n",
              tf->trapno, cpuid(), tf->eip, rcr2());
      panic("trap");
    }
    // In user space, assume process misbehaved.
    cprintf("pid %d %s: trap %d err %d on cpu %d "
            "eip 0x%x addr 0x%x--kill proc\n",
            myproc()->pid, myproc()->name, tf->trapno,
            tf->err, cpuid(), tf->eip, rcr2());
    myproc()->killed = 1;
  }

  // Force process exit if it has been killed and is in user space.
  // (If it is still executing in the kernel, let it keep running
  // until it gets to the regular system call return.)
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();

  // Force process to give up CPU on clock tick.
  // If interrupts were on while locks held, would need to check nlock.
  if(myproc() && myproc()->state == RUNNING && tf->trapno == T_IRQ0+IRQ_TIMER)
  {
    //cprintf("tick %d\n", ticks);
    if(myproc()->p_lock == 1){
      if(ticks>=100){
        // cprintf("\n");
        // cprintf("L_priorityBoosting!\n");
        // cprintf("\n");
        myproc()->p_lock = 0;
        myproc()->scheunlocked = 1;
        ticks=0;
        priorityBoosting();
        yield();
      }
    }
    else{
      if(ticks>=100){
        // cprintf("\n");
        // cprintf("priorityBoosting!\n");
        // cprintf("\n");
        ticks=0;
        priorityBoosting();
      }
      
      if(myproc()->p_tick == myproc()->time_quantum){
        if(myproc()->queue_level==2){
          if(myproc()->p_priority!=0){
            myproc()->p_priority--;
            //cprintf("proc: %d level: %d priority: %d\n ", myproc()->pid, myproc()->queue_level, myproc()->p_priority);
            //cprintf("\n");
          }
        }
        else{
          myproc()->queue_level++;
          myproc()->time_quantum = 2*(myproc()->queue_level)+4;
          //cprintf("proc: %d level: %d priority: %d\n ", myproc()->pid, myproc()->queue_level, myproc()->p_priority);
          //cprintf("\n");
      
        }
        myproc()->p_tick=0;
      }
      yield();
    }
  }
  // Check if the process has been killed since we yielded
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();
}
