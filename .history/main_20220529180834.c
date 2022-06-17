#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <xcb/xcb.h>

xcb_atom_t getatom(xcb_connection_t* c, char *atom_name)
{
    xcb_intern_atom_cookie_t atom_cookie;
    xcb_atom_t atom;
    xcb_intern_atom_reply_t *rep;

    atom_cookie = xcb_intern_atom(c, 0, strlen(atom_name), atom_name);
    rep = xcb_intern_atom_reply(c, atom_cookie, NULL);
    if (NULL != rep)
    {
        atom = rep->atom;
        free(rep);
        printf("\natom: %ld",atom);
        fflush(stdout);
        return atom;
    }
    printf("\nError getting atom.\n");
    exit(1);
}

int main() {
  xcb_generic_error_t *e;
  int i,j,k;

  xcb_connection_t* c = xcb_connect(NULL, NULL);
  xcb_atom_t net_client_list = getatom(c,"_NET_CLIENT_LIST");
  xcb_atom_t net_wm_visible_name = getatom(c,"_NET_WM_VISIBLE_NAME");

  xcb_screen_t* screen = xcb_setup_roots_iterator(xcb_get_setup(c)).data;

  xcb_get_property_cookie_t prop_cookie_list,prop_cookie;
  xcb_get_property_reply_t *reply_prop_list,*reply_prop;

  prop_cookie_list = xcb_get_property(c, 0, screen->root, net_client_list, XCB_GET_PROPERTY_TYPE_ANY, 0, 100);
  reply_prop_list = xcb_get_property_reply(c, prop_cookie_list, &e);
  if(e) {
    printf("\nError: %d",e->error_code);
    free(e);
  }
  if(reply_prop_list) {
    int value_len = xcb_get_property_value_length(reply_prop_list);
    if(value_len) {
      xcb_window_t* win = xcb_get_property_value(reply_prop_list);
      for(i=0; i<value_len/4; i++) {
        prop_cookie = xcb_get_property(c, 0, win[i], net_wm_visible_name, XCB_GET_PROPERTY_TYPE_ANY, 0, 1000);
        reply_prop = xcb_get_property_reply(c, prop_cookie, &e);
        if(e) {
          printf("\nError: %d",e->error_code);
          free(e);
        }
        if(reply_prop) {
          int value_len2 = xcb_get_property_value_length(reply_prop);
          if(value_len2) {
            char* name = malloc(value_len2+1);
            strncpy(name,xcb_get_property_value(reply_prop),value_len2);
            name[value_len2] = '\0';
            printf("\nName: %s",name);
            fflush(stdout);
            free(name);
          }
          free(reply_prop);
        }
      }
    }
    free(reply_prop_list);
  }
  printf("\n\n");
  fflush(stdout);
  exit(0);
}