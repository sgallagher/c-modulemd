/*
 * This file is part of libmodulemd
 * Copyright (C) 2017-2018 Stephen Gallagher
 *
 * Fedora-License-Identifier: MIT
 * SPDX-2.0-License-Identifier: MIT
 * SPDX-3.0-License-Identifier: MIT
 *
 * This program is free software.
 * For more information on the license, see COPYING.
 * For more information on free software, see <https://www.gnu.org/philosophy/free-sw.en.html>.
 */

#include <glib.h>
#include <glib/gstdio.h>
#include <locale.h>
#include <signal.h>

#include "modulemd-defaults-v1.h"
#include "private/glib-extensions.h"
#include "private/modulemd-defaults-v1-private.h"
#include "private/modulemd-translation-entry-private.h"
#include "private/modulemd-subdocument-info-private.h"
#include "private/modulemd-yaml.h"
#include "private/test-utils.h"

static void
defaults_test_construct (CommonMmdTestFixture *fixture,
                         gconstpointer user_data)
{
  g_autoptr (ModulemdDefaultsV1) defaults = NULL;

  /* Test new() with a valid module name */
  defaults = modulemd_defaults_v1_new ("foo");
  g_assert_nonnull (defaults);
  g_assert_true (MODULEMD_IS_DEFAULTS (defaults));
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (defaults));
  g_clear_object (&defaults);

  /* Test new() with a NULL module_name */
  modulemd_test_signal = 0;
  signal (SIGTRAP, modulemd_test_signal_handler);
  defaults = modulemd_defaults_v1_new (NULL);
  g_assert_cmpint (modulemd_test_signal, ==, SIGTRAP);
  g_clear_object (&defaults);


  /* Test object instantiation with a valid module name */
  // clang-format off
  defaults = g_object_new (MODULEMD_TYPE_DEFAULTS_V1,
                           "module-name", "bar",
                           NULL);
  // clang-format on
  g_assert_nonnull (defaults);
  g_assert_true (MODULEMD_IS_DEFAULTS (defaults));
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (defaults));
  g_clear_object (&defaults);

  /* Test object instantiation with a NULL module name */
  modulemd_test_signal = 0;
  signal (SIGTRAP, modulemd_test_signal_handler);
  // clang-format off
  defaults = g_object_new (MODULEMD_TYPE_DEFAULTS_V1,
                           "module-name", NULL,
                           NULL);
  // clang-format on
  g_assert_cmpint (modulemd_test_signal, ==, SIGTRAP);
  g_clear_object (&defaults);

  /* Test object instantiation without specifying the module name */
  modulemd_test_signal = 0;
  signal (SIGTRAP, modulemd_test_signal_handler);
  // clang-format off
  defaults = g_object_new (MODULEMD_TYPE_DEFAULTS_V1, NULL);
  // clang-format on
  g_assert_cmpint (modulemd_test_signal, ==, SIGTRAP);
  g_clear_object (&defaults);
}


static void
defaults_test_copy (CommonMmdTestFixture *fixture, gconstpointer user_data)
{
  g_autoptr (ModulemdDefaultsV1) defaults = NULL;
  g_autoptr (ModulemdDefaultsV1) copied_defaults = NULL;

  defaults = modulemd_defaults_v1_new ("foo");
  g_assert_nonnull (defaults);
  g_assert_true (MODULEMD_IS_DEFAULTS (defaults));
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (defaults));

  copied_defaults = MODULEMD_DEFAULTS_V1 (
    modulemd_defaults_copy (MODULEMD_DEFAULTS (defaults)));
  g_assert_nonnull (copied_defaults);
  g_assert_true (MODULEMD_IS_DEFAULTS (copied_defaults));
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (copied_defaults));
  g_assert_cmpuint (
    modulemd_defaults_get_mdversion (MODULEMD_DEFAULTS (defaults)),
    ==,
    modulemd_defaults_get_mdversion (MODULEMD_DEFAULTS (copied_defaults)));

  g_assert_cmpstr (
    modulemd_defaults_get_module_name (MODULEMD_DEFAULTS (defaults)),
    ==,
    modulemd_defaults_get_module_name (MODULEMD_DEFAULTS (copied_defaults)));

  g_assert_cmpstr (
    modulemd_defaults_v1_get_default_stream (defaults, NULL),
    ==,
    modulemd_defaults_v1_get_default_stream (copied_defaults, NULL));

  /* TODO: deep compare of profile copying */
  g_clear_object (&defaults);
  g_clear_object (&copied_defaults);

  // clang-format off
  defaults = g_object_new (MODULEMD_TYPE_DEFAULTS_V1,
                          "module-name", "foo",
                          NULL);
  // clang-format on
  g_assert_nonnull (defaults);
  g_assert_true (MODULEMD_IS_DEFAULTS (defaults));
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (defaults));

  copied_defaults = MODULEMD_DEFAULTS_V1 (
    modulemd_defaults_copy (MODULEMD_DEFAULTS (defaults)));
  g_assert_nonnull (copied_defaults);
  g_assert_true (MODULEMD_IS_DEFAULTS (copied_defaults));
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (copied_defaults));
  g_assert_cmpuint (
    modulemd_defaults_get_mdversion (MODULEMD_DEFAULTS (defaults)),
    ==,
    modulemd_defaults_get_mdversion (MODULEMD_DEFAULTS (copied_defaults)));

  g_assert_cmpstr (
    modulemd_defaults_get_module_name (MODULEMD_DEFAULTS (defaults)),
    ==,
    modulemd_defaults_get_module_name (MODULEMD_DEFAULTS (copied_defaults)));

  g_assert_cmpstr (
    modulemd_defaults_v1_get_default_stream (defaults, NULL),
    ==,
    modulemd_defaults_v1_get_default_stream (copied_defaults, NULL));

  /* TODO: deep compare of profile copying */
}


static void
defaults_test_get_set_default_stream (CommonMmdTestFixture *fixture,
                                      gconstpointer user_data)
{
  g_autoptr (ModulemdDefaultsV1) defaults = NULL;

  defaults = modulemd_defaults_v1_new ("foo");
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (defaults));

  /* Test set_default_stream() with valid string */
  modulemd_defaults_v1_set_default_stream (defaults, "latest", NULL);
  g_assert_cmpstr (
    modulemd_defaults_v1_get_default_stream (defaults, NULL), ==, "latest");

  /* TODO: Remove the default stream */

  /* TODO: Get, set and remove default streams for an intent */
}


static void
defaults_test_validate (CommonMmdTestFixture *fixture, gconstpointer user_data)
{
  g_autoptr (ModulemdDefaultsV1) defaults = NULL;

  defaults = modulemd_defaults_v1_new ("foo");
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (defaults));

  /* Currently there is no way for validation to fail, since all of its
   * properties are forced to be valid at object instantiation or are optional.
   */
  g_assert_true (
    modulemd_defaults_validate (MODULEMD_DEFAULTS (defaults), NULL));
}


static void
defaults_test_profiles (CommonMmdTestFixture *fixture, gconstpointer user_data)
{
  g_autoptr (ModulemdDefaultsV1) defaults = NULL;
  g_auto (GStrv) streams = NULL;
  g_auto (GStrv) profiles = NULL;

  defaults = modulemd_defaults_v1_new ("foo");
  g_assert_true (MODULEMD_IS_DEFAULTS_V1 (defaults));

  /* Add profiles "server" and "client" to the streams "stable" and
   * "experimental".
   */
  modulemd_defaults_v1_add_default_profile_for_stream (
    defaults, "stable", "server", NULL);
  modulemd_defaults_v1_add_default_profile_for_stream (
    defaults, "stable", "client", NULL);
  modulemd_defaults_v1_add_default_profile_for_stream (
    defaults, "experimental", "server", NULL);
  modulemd_defaults_v1_add_default_profile_for_stream (
    defaults, "experimental", "client", NULL);

  /* Get the list of streams with default profiles back */
  streams = modulemd_defaults_v1_get_streams_with_default_profiles_as_strv (
    defaults, NULL);

  /* The streams must be in lexical order */
  g_assert_cmpstr (streams[0], ==, "experimental");
  g_assert_cmpstr (streams[1], ==, "stable");
  g_assert_null (streams[2]);
  g_clear_pointer (&streams, g_strfreev);

  /* The profiles must be in lexical order */
  profiles = modulemd_defaults_v1_get_default_profiles_for_stream_as_strv (
    defaults, "stable", NULL);
  g_assert_cmpstr (profiles[0], ==, "client");
  g_assert_cmpstr (profiles[1], ==, "server");
  g_assert_null (profiles[2]);
  g_clear_pointer (&profiles, g_strfreev);

  profiles = modulemd_defaults_v1_get_default_profiles_for_stream_as_strv (
    defaults, "experimental", NULL);
  g_assert_cmpstr (profiles[0], ==, "client");
  g_assert_cmpstr (profiles[1], ==, "server");
  g_assert_null (profiles[2]);
  g_clear_pointer (&profiles, g_strfreev);

  /* Verify that looking up a nonexistent stream returns NULL */
  profiles = modulemd_defaults_v1_get_default_profiles_for_stream_as_strv (
    defaults, "nonexistent", NULL);
  g_assert_null (profiles);

  /* Test adding an empty set of profiles */
  modulemd_defaults_v1_set_empty_default_profiles_for_stream (
    defaults, "empty", NULL);

  streams = modulemd_defaults_v1_get_streams_with_default_profiles_as_strv (
    defaults, NULL);
  /* The streams must be in lexical order */
  g_assert_cmpstr (streams[0], ==, "empty");
  g_assert_cmpstr (streams[1], ==, "experimental");
  g_assert_cmpstr (streams[2], ==, "stable");
  g_assert_null (streams[3]);
  g_clear_pointer (&streams, g_strfreev);

  /* Test that looking up these profiles returns a zero-length array */
  profiles = modulemd_defaults_v1_get_default_profiles_for_stream_as_strv (
    defaults, "empty", NULL);
  g_assert_nonnull (profiles);
  g_assert_null (profiles[0]);
  g_clear_pointer (&profiles, g_strfreev);

  /* Test removing the profiles for a stream */
  modulemd_defaults_v1_remove_default_profiles_for_stream (
    defaults, "empty", NULL);
  profiles = modulemd_defaults_v1_get_default_profiles_for_stream_as_strv (
    defaults, "empty", NULL);
  g_assert_null (profiles);

  streams = modulemd_defaults_v1_get_streams_with_default_profiles_as_strv (
    defaults, NULL);
  /* The streams must be in lexical order */
  g_assert_cmpstr (streams[0], ==, "experimental");
  g_assert_cmpstr (streams[1], ==, "stable");
  g_assert_null (streams[2]);
  g_clear_pointer (&streams, g_strfreev);
}


static void
defaults_test_parse_yaml (CommonMmdTestFixture *fixture,
                          gconstpointer user_data)
{
  MMD_INIT_YAML_PARSER (parser);
  MMD_INIT_YAML_EVENT (event);
  g_autofree gchar *yaml_path = NULL;
  g_autoptr (ModulemdDefaultsV1) defaults = NULL;
  int yaml_ret;
  g_autoptr (FILE) yaml_stream = NULL;
  g_autoptr (GError) error = NULL;
  g_autoptr (ModulemdSubdocumentInfo) subdoc = NULL;


  /* Validate that we can read the specification without issues */
  yaml_path = g_strdup_printf ("%s/mod-defaults/spec.v1.yaml",
                               g_getenv ("MESON_SOURCE_ROOT"));
  g_assert_nonnull (yaml_path);

  yaml_stream = g_fopen (yaml_path, "rb");
  g_assert_nonnull (yaml_stream);

  yaml_parser_set_input_file (&parser, yaml_stream);

  /* The first event must be the stream start */
  yaml_ret = yaml_parser_parse (&parser, &event);
  g_assert_true (yaml_ret);
  g_assert_cmpint (event.type, ==, YAML_STREAM_START_EVENT);
  yaml_event_delete (&event);

  subdoc = modulemd_yaml_parse_document_type (&parser);
  g_assert_nonnull (subdoc);
  g_assert_null (modulemd_subdocument_info_get_gerror (subdoc));

  g_assert_cmpint (modulemd_subdocument_info_get_doctype (subdoc),
                   ==,
                   MODULEMD_YAML_DOC_DEFAULTS);
  g_assert_cmpint (modulemd_subdocument_info_get_mdversion (subdoc),
                   ==,
                   MD_DEFAULTS_VERSION_ONE);
  g_assert_nonnull (modulemd_subdocument_info_get_yaml (subdoc));
  g_assert_cmpstr (
    modulemd_subdocument_info_get_yaml (subdoc),
    ==,
    "document: modulemd-defaults\nversion: 1\ndata:\n  module: "
    "foo\n  "
    "stream: x.y\n  profiles:\n    'x.y': []\n    bar: [baz, snafu]\n  "
    "intents:\n    desktop:\n      stream: y.z\n      profiles:\n        "
    "'y.z': [blah]\n        'x.y': [other]\n    server:\n      stream: x.y\n  "
    "    profiles:\n        'x.y': []\n");

  /* Parse the data section and validate the content */
  defaults = modulemd_defaults_v1_parse_yaml (subdoc, &error);
  g_assert_nonnull (defaults);
  g_assert_null (error);

  g_assert_true (
    modulemd_defaults_validate (MODULEMD_DEFAULTS (defaults), &error));
}


static void
defaults_test_emit_yaml (CommonMmdTestFixture *fixture,
                         gconstpointer user_data)
{
  MMD_INIT_YAML_EMITTER (emitter);
  MMD_INIT_YAML_EVENT (event);
  MMD_INIT_YAML_STRING (&emitter, yaml_string);
  g_autoptr (GError) error = NULL;
  g_autoptr (ModulemdDefaultsV1) defaults = modulemd_defaults_v1_new ("foo");

  g_assert_true (mmd_emitter_start_stream (&emitter, &error));
  g_assert_true (modulemd_defaults_v1_emit_yaml (defaults, &emitter, &error));
  g_assert_true (mmd_emitter_end_stream (&emitter, &error));
  g_assert_nonnull (yaml_string->str);
  g_assert_cmpstr (yaml_string->str,
                   ==,
                   "---\ndocument: modulemd-defaults\nversion: 1\ndata:\n  "
                   "module: foo\n...\n");


  /* Add a default stream and emit again */
  modulemd_defaults_v1_set_default_stream (defaults, "latest", NULL);

  MMD_REINIT_YAML_STRING (&emitter, yaml_string);
  g_assert_true (mmd_emitter_start_stream (&emitter, &error));
  g_assert_true (modulemd_defaults_v1_emit_yaml (defaults, &emitter, &error));
  g_assert_true (mmd_emitter_end_stream (&emitter, &error));
  g_assert_nonnull (yaml_string->str);
  g_assert_cmpstr (yaml_string->str,
                   ==,
                   "---\ndocument: modulemd-defaults\nversion: 1\ndata:\n  "
                   "module: foo\n  stream: latest\n...\n");

  /* Add an empty profile default and emit again */
  modulemd_defaults_v1_set_empty_default_profiles_for_stream (
    defaults, "libonly", NULL);

  MMD_REINIT_YAML_STRING (&emitter, yaml_string);
  g_assert_true (mmd_emitter_start_stream (&emitter, &error));
  g_assert_true (modulemd_defaults_v1_emit_yaml (defaults, &emitter, &error));
  g_assert_true (mmd_emitter_end_stream (&emitter, &error));
  g_assert_nonnull (yaml_string->str);
  g_assert_cmpstr (
    yaml_string->str,
    ==,
    "---\ndocument: modulemd-defaults\nversion: 1\ndata:\n  "
    "module: foo\n  stream: latest\n  profiles:\n    libonly: []\n...\n");

  /* Add a real profile default and emit again */
  modulemd_defaults_v1_add_default_profile_for_stream (
    defaults, "latest", "bar", NULL);

  MMD_REINIT_YAML_STRING (&emitter, yaml_string);
  g_assert_true (mmd_emitter_start_stream (&emitter, &error));
  g_assert_true (modulemd_defaults_v1_emit_yaml (defaults, &emitter, &error));
  g_assert_true (mmd_emitter_end_stream (&emitter, &error));
  g_assert_nonnull (yaml_string->str);
  g_assert_cmpstr (yaml_string->str,
                   ==,
                   "---\ndocument: modulemd-defaults\nversion: 1\ndata:\n  "
                   "module: foo\n  stream: latest\n  profiles:\n    latest: "
                   "[bar]\n    libonly: "
                   "[]\n...\n");

  /* Add another real profile default to the same stream and emit again */
  modulemd_defaults_v1_add_default_profile_for_stream (
    defaults, "latest", "baz", NULL);

  MMD_REINIT_YAML_STRING (&emitter, yaml_string);
  g_assert_true (mmd_emitter_start_stream (&emitter, &error));
  g_assert_true (modulemd_defaults_v1_emit_yaml (defaults, &emitter, &error));
  g_assert_true (mmd_emitter_end_stream (&emitter, &error));
  g_assert_nonnull (yaml_string->str);
  g_assert_cmpstr (yaml_string->str,
                   ==,
                   "---\ndocument: modulemd-defaults\nversion: 1\ndata:\n  "
                   "module: foo\n  stream: latest\n  profiles:\n    latest: "
                   "[bar, baz]\n    libonly: "
                   "[]\n...\n");


  /* Add an intent-specific default stream and emit again */
  modulemd_defaults_v1_set_default_stream (defaults, "earliest", "intense");

  MMD_REINIT_YAML_STRING (&emitter, yaml_string);
  g_assert_true (mmd_emitter_start_stream (&emitter, &error));
  g_assert_true (modulemd_defaults_v1_emit_yaml (defaults, &emitter, &error));
  g_assert_true (mmd_emitter_end_stream (&emitter, &error));
  g_assert_nonnull (yaml_string->str);
  g_assert_cmpstr (
    yaml_string->str,
    ==,
    "---\ndocument: modulemd-defaults\nversion: 1\ndata:\n  "
    "module: foo\n  stream: latest\n  profiles:\n    latest: "
    "[bar, baz]\n    libonly: "
    "[]\n  intents:\n    intense:\n      stream: earliest\n...\n");

  /* Add an intent-specific profile default and emit again */
  modulemd_defaults_v1_add_default_profile_for_stream (
    defaults, "earliest", "client", "intense");

  MMD_REINIT_YAML_STRING (&emitter, yaml_string);
  g_assert_true (mmd_emitter_start_stream (&emitter, &error));
  g_assert_true (modulemd_defaults_v1_emit_yaml (defaults, &emitter, &error));
  g_assert_true (mmd_emitter_end_stream (&emitter, &error));
  g_assert_nonnull (yaml_string->str);
  g_assert_cmpstr (yaml_string->str,
                   ==,
                   "---\ndocument: modulemd-defaults\nversion: 1\ndata:\n  "
                   "module: foo\n  stream: latest\n  profiles:\n    latest: "
                   "[bar, baz]\n    libonly: "
                   "[]\n  intents:\n    intense:\n      stream: earliest\n    "
                   "  profiles:\n        earliest: [client]\n...\n");
}


int
main (int argc, char *argv[])
{
  setlocale (LC_ALL, "");

  g_test_init (&argc, &argv, NULL);
  g_test_bug_base ("https://bugzilla.redhat.com/show_bug.cgi?id=");

  // Define the tests.
  g_test_add ("/modulemd/v2/defaults/v1/construct",
              CommonMmdTestFixture,
              NULL,
              NULL,
              defaults_test_construct,
              NULL);

  g_test_add ("/modulemd/v2/defaults/v1/copy",
              CommonMmdTestFixture,
              NULL,
              NULL,
              defaults_test_copy,
              NULL);

  g_test_add ("/modulemd/v2/defaults/v1/default_stream",
              CommonMmdTestFixture,
              NULL,
              NULL,
              defaults_test_get_set_default_stream,
              NULL);

  g_test_add ("/modulemd/v2/defaults/v1/validate",
              CommonMmdTestFixture,
              NULL,
              NULL,
              defaults_test_validate,
              NULL);

  g_test_add ("/modulemd/v2/defaults/v1/profile_defaults",
              CommonMmdTestFixture,
              NULL,
              NULL,
              defaults_test_profiles,
              NULL);

  g_test_add ("/modulemd/v2/defaults/v1/yaml/parse",
              CommonMmdTestFixture,
              NULL,
              NULL,
              defaults_test_parse_yaml,
              NULL);

  g_test_add ("/modulemd/v2/defaults/v1/yaml/emit",
              CommonMmdTestFixture,
              NULL,
              NULL,
              defaults_test_emit_yaml,
              NULL);

  return g_test_run ();
}
