{
  "targets": [
    {
      "target_name": "qconf",
      "sources": [ "qconf.cc" ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "libraries": ["-lqconf"],
      "link_settings": {
        "libraries": ["-L<!(echo $QCONF_INSTALL)/lib"]
      },
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "<!(echo $QCONF_INSTALL)/include",
        "/usr/local/qconf/include",
        "/usr/local/include/qconf"
      ]
    }
  ]
}
