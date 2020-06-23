#include <stdio.h>

#define BOXES 20
#define STACK_SIZE 1024

struct box {
    unsigned a, b, c;
    unsigned bits;
};

unsigned box_num;
struct box boxes[BOXES];

struct pyramid {
    unsigned w, l, h;
    unsigned bmask;
};
struct pyramid stack[STACK_SIZE];
struct pyramid get, put;
unsigned stack_top = 0;
unsigned answer;
unsigned max_mask;

void solve(void)
{
    answer = 0;
    stack_top = 0;
    for (unsigned x = 0; x < box_num; x++) {
        //c for height
        stack[stack_top].w = boxes[x].a;
        stack[stack_top].l = boxes[x].b;
        stack[stack_top].h = boxes[x].c;
        stack[stack_top].bmask = boxes[x].bits;
        stack_top++;
        //a for height
        stack[stack_top].w = boxes[x].b;
        stack[stack_top].l = boxes[x].c;
        stack[stack_top].h = boxes[x].a;
        stack[stack_top].bmask = boxes[x].bits;
        stack_top++;
        //b for height
        stack[stack_top].w = boxes[x].c;
        stack[stack_top].l = boxes[x].a;
        stack[stack_top].h = boxes[x].b;
        stack[stack_top].bmask = boxes[x].bits;
        stack_top++;
    }
/*    for (unsigned c = 0; c < stack_top; c++) {
        printf("w = %u, l = %u, h = %u, bits = %#x\n", stack[c].w, stack[c].l, stack[c].h, stack[c].bmask);
    }*/
    while (stack_top != 0) {
        get = stack[--stack_top];
//        printf("get.w = %u, get.l = %u, get.h = %u, get.bmask = %#x\n", get.w, get.l, get.h, get.bmask);
        if (answer < get.h)  {
            answer = get.h;
        }
        for (unsigned y = 0; y < box_num; y++) {
            if ((get.bmask & boxes[y].bits) == 0 && get.bmask != max_mask) {
                //c for height
//                printf("a = %u, b = %u, c = %u\n", boxes[y].a, boxes[y].b, boxes[y].c);
                if ((get.w > boxes[y].a && get.l > boxes[y].b)
                 || (get.w > boxes[y].b && get.l > boxes[y].a)) {
//                    printf("a");
//                    printf("boxes.c = %u, h = %u\n", boxes[y].c, get.h + boxes[y].c);
                    put.w = boxes[y].a;
                    put.l = boxes[y].b;
                    put.h = get.h + boxes[y].c;
                    put.bmask = get.bmask | boxes[y].bits;
                    stack[stack_top++] = put;
                } else {
//                    printf("fuck c\n");
                }
                //a for height
                if ((get.w > boxes[y].b && get.l > boxes[y].c)
                 || (get.w > boxes[y].c && get.l > boxes[y].b)) {
//                    printf("b");
//                    printf("boxes.a = %u, h = %u\n", boxes[y].a, get.h + boxes[y].a);
                    put.w = boxes[y].b;
                    put.l = boxes[y].c;
                    put.h = get.h + boxes[y].a;
                    put.bmask = get.bmask | boxes[y].bits;
                    stack[stack_top++] = put;
                } else {
//                    printf("fuck a\n");
                }
                //b for height
                if ((get.w > boxes[y].a && get.l > boxes[y].c)
                 || (get.w > boxes[y].c && get.l > boxes[y].a)) {
//                    printf("c");
//                    printf("boxes.b = %u, h = %u\n", boxes[y].b, get.h + boxes[y].b);
                    put.w = boxes[y].a;
                    put.l = boxes[y].c;
                    put.h = get.h + boxes[y].b;
                    put.bmask = get.bmask | boxes[y].bits;
                    stack[stack_top++] = put;
                } else {
//                    printf("fuck b\n");
                }
            }
        }
//        printf("stack_top = %u\n", stack_top);
    }
}

int main(void)
{
    unsigned cases;

    for (unsigned x = 0; x < BOXES; x++) {
        boxes[x].bits = 1 << x;
    }
/*    for (unsigned x = 0; x < BOXES; x++) {
        printf("boxes[%u] = %#x\n", x, boxes[x].bits);
    }*/

    scanf("%u", &cases);
    cases++;
    for (unsigned c = 1; c < cases; c++) {
        scanf("%u", &box_num);
        max_mask = ((~boxes[box_num].bits | boxes[box_num].bits) << box_num) >> (sizeof(unsigned) * 8 - box_num);
        printf("max_mask = %#x\n", max_mask);
        for (unsigned x = 0; x < box_num; x++) {
            scanf("%u %u %u", &boxes[x].a, &boxes[x].b, &boxes[x].c);
        }
        solve();
        printf("#%u %u\n\n", c, answer);
    }

    return 0;
}
