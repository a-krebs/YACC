CP_TEST_FILE= -rm -f $@ && cp $< $@

checkpoint_3: 0.pal 1.pal 2.pal 3.pal 4.pal 5.pal 6.pal 7.pal 8.pal 9.pal

0.pal: $(TEST_FILES)/semantic/checkpoint_3_0.pal
	$(CP_TEST_FILE)

1.pal: $(TEST_FILES)/semantic/checkpoint_3_1.pal
	$(CP_TEST_FILE)

2.pal: $(TEST_FILES)/semantic/checkpoint_3_2.pal
	$(CP_TEST_FILE)

3.pal: $(TEST_FILES)/semantic/checkpoint_3_3.pal
	$(CP_TEST_FILE)

4.pal: $(TEST_FILES)/full/checkpoint_3_4.pal
	$(CP_TEST_FILE)

5.pal: $(TEST_FILES)/full/checkpoint_3_5.pal
	$(CP_TEST_FILE)

6.pal: $(TEST_FILES)/full/checkpoint_3_6.pal
	$(CP_TEST_FILE)

7.pal: $(TEST_FILES)/full/checkpoint_3_7.pal
	$(CP_TEST_FILE)

8.pal: $(TEST_FILES)/full/checkpoint_3_8.pal
	$(CP_TEST_FILE)

9.pal: $(TEST_FILES)/full/checkpoint_3_9.pal
	$(CP_TEST_FILE)
