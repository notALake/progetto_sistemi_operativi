#include "./headers/pcb.h"

static struct list_head pcbFree_h;
static pcb_t pcbFree_table[MAXPROC];
static int next_pid = 1;

void initPcbs()
{
  INIT_LIST_HEAD(&pcbFree_h);

  for(int c=0; c<MAXPROC; c++)
  {
    list_add(&(pcbFree_table[c].p_list), &pcbFree_h);
  }
}

void freePcb(pcb_t* p)
{
  list_add(&p->p_list, &pcbFree_h);
}

pcb_t* allocPcb()
{
  if(list_empty(&pcbFree_h))
    return NULL;
  else
  {
    struct list_head *entry=pcbFree_h.next;

    list_del(entry);
    pcb_t *p=container_of(entry, pcb_t, p_list);

    p->p_pid=next_pid++;
    p->p_parent=NULL;

    INIT_LIST_HEAD(&p->p_child);
    INIT_LIST_HEAD(&p->p_sib);

    p->p_time=0;
    p->p_semAdd=NULL;
    p->p_supportStruct=NULL;
    p->p_prio=0;

    p->p_s.entry_hi=0;
    p->p_s.cause=0;
    p->p_s.status=0;
    p->p_s.pc_epc=0;
    p->p_s.mie=0;

    for(int c=0; c<STATE_GPR_LEN; c++)
    {
      p->p_s.gpr[c]=0;
    }

    return p;
  }
}

void mkEmptyProcQ(struct list_head* head)
{
  INIT_LIST_HEAD(head);
}

int emptyProcQ(struct list_head* head)
{
  return list_empty(head);
}

void insertProcQ(struct list_head* head, pcb_t* p)
{
  /*
   * Scans the list looking for an element with lower priority.
   * If found, inserts the given PCB before it
   */
  struct list_head* iter;
  list_for_each(iter, head)
  {
    /* Retrieves the PCB containing the current list element */
    pcb_t* item = container_of(iter, pcb_t, p_list);
    if (item->p_prio < p->p_prio)
    {
        list_add(&p->p_list, iter->prev);
        return;
    }
  }
  /* If no lower priority element is found, appends the PCB to the tail */
  list_add_tail(&p->p_list, head);
}

pcb_t* headProcQ(struct list_head* head)
{
  /* If the list is empty, returns NULL */
  if(list_empty(head)){return NULL;}
  /* Otherwise, returns the pointer to the first PCB */
  pcb_t* p = container_of(head->next, pcb_t, p_list);
  return p;
}

pcb_t* removeProcQ(struct list_head* head)
{
  /* If the list is empty, returns NULL */
  if(list_empty(head)){return NULL;}
  /* Saves a pointer to the first element before removing it */
  struct list_head *entry=head->next;
  list_del(entry);
  /* Retrieves the PCB of the removed element */
  pcb_t *p=container_of(entry, pcb_t, p_list);
  return p;
}

pcb_t* outProcQ(struct list_head* head, pcb_t* p)
{
  /*
   * Scans the list looking for a PCB equal to the one given.
   * If found, removes the entry from the list.
   */
  struct list_head* iter;
  list_for_each(iter, head)
  {
    pcb_t* item = container_of(iter, pcb_t, p_list);
    if (item==p)
    {
      list_del(iter);
      return p;
    }
  }
  /* If not found, returns NULL */
  return NULL;
}

int emptyChild(pcb_t* p)
{
  if (p==NULL) return 1;
  return list_empty(&p->p_child);
}

void insertChild(pcb_t* prnt, pcb_t* p)
{
  p->p_parent = prnt;
  list_add(&p->p_sib, &prnt->p_child);
}

pcb_t* removeChild(pcb_t* p)
{
  if(list_empty(&p->p_child)){return NULL;}
  pcb_t* first = container_of(p->p_child.next, pcb_t, p_sib);
  list_del(&first->p_sib);
  first->p_parent = NULL;
  return first;
}

pcb_t* outChild(pcb_t* p)
{
  if(p->p_parent==NULL){return NULL;}
  list_del(&p->p_sib);
  p->p_parent = NULL;
  return p;
}
