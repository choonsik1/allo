module tb_pe_array_cordic_hyperbolic_rotation();

    parameter CLOCKCYCLE = 10;

    logic           clk;
    logic           rst_n;

    // router io
    logic           rtr_rx_col_dwn_rq   [7:0];
    logic [3:0]     rtr_rx_col_dwn_id   [7:0];
    logic           rtr_rx_col_dwn_mode [7:0];
    logic [3:0]     rtr_rx_col_dwn_addr [7:0];
    logic [15:0]    rtr_rx_col_dwn_data [7:0];
    logic           rtr_rx_col_dwn_gt   [7:0];

    logic           rtr_tx_col_upp_rq   [7:0];
    logic [3:0]     rtr_tx_col_upp_id   [7:0];
    logic           rtr_tx_col_upp_mode [7:0];
    logic [3:0]     rtr_tx_col_upp_addr [7:0];
    logic [15:0]    rtr_tx_col_upp_data [7:0];
    logic           rtr_tx_col_upp_gt   [7:0];

    logic           rtr_rx_col_upp_rq   [7:0];
    logic [3:0]     rtr_rx_col_upp_id   [7:0];
    logic           rtr_rx_col_upp_mode [7:0];
    logic [3:0]     rtr_rx_col_upp_addr [7:0];
    logic [15:0]    rtr_rx_col_upp_data [7:0];
    logic           rtr_rx_col_upp_gt   [7:0];

    logic           rtr_tx_col_dwn_rq   [7:0];
    logic [3:0]     rtr_tx_col_dwn_id   [7:0];
    logic           rtr_tx_col_dwn_mode [7:0];
    logic [3:0]     rtr_tx_col_dwn_addr [7:0];
    logic [15:0]    rtr_tx_col_dwn_data [7:0];
    logic           rtr_tx_col_dwn_gt   [7:0];

    logic           rtr_rx_row_rgt_rq   [7:0];
    logic [3:0]     rtr_rx_row_rgt_id   [7:0];
    logic           rtr_rx_row_rgt_mode [7:0];
    logic [3:0]     rtr_rx_row_rgt_addr [7:0];
    logic [15:0]    rtr_rx_row_rgt_data [7:0];
    logic           rtr_rx_row_rgt_gt   [7:0];

    logic           rtr_tx_row_lft_rq   [7:0];
    logic [3:0]     rtr_tx_row_lft_id   [7:0];
    logic           rtr_tx_row_lft_mode [7:0];
    logic [3:0]     rtr_tx_row_lft_addr [7:0];
    logic [15:0]    rtr_tx_row_lft_data [7:0];
    logic           rtr_tx_row_lft_gt   [7:0];

    logic           rtr_rx_row_lft_rq   [7:0];
    logic [3:0]     rtr_rx_row_lft_id   [7:0];
    logic           rtr_rx_row_lft_mode [7:0];
    logic [3:0]     rtr_rx_row_lft_addr [7:0];
    logic [15:0]    rtr_rx_row_lft_data [7:0];
    logic           rtr_rx_row_lft_gt   [7:0];

    logic           rtr_tx_row_rgt_rq   [7:0];
    logic [3:0]     rtr_tx_row_rgt_id   [7:0];
    logic           rtr_tx_row_rgt_mode [7:0];
    logic [3:0]     rtr_tx_row_rgt_addr [7:0];
    logic [15:0]    rtr_tx_row_rgt_data [7:0];
    logic           rtr_tx_row_rgt_gt   [7:0];

    // systolic io
    logic           sys_rx_top_rq   [7:0];
    logic [15:0]    sys_rx_top_data [7:0];
    logic           sys_rx_top_gt   [7:0];

    logic           sys_tx_top_rq   [7:0];
    logic [15:0]    sys_tx_top_data [7:0];
    logic           sys_tx_top_gt   [7:0];

    logic           sys_rx_btm_rq   [7:0];
    logic [15:0]    sys_rx_btm_data [7:0];
    logic           sys_rx_btm_gt   [7:0];

    logic           sys_tx_btm_rq   [7:0];
    logic [15:0]    sys_tx_btm_data [7:0];
    logic           sys_tx_btm_gt   [7:0];

    logic           sys_rx_lft_rq   [7:0];
    logic [15:0]    sys_rx_lft_data [7:0];
    logic           sys_rx_lft_gt   [7:0];

    logic           sys_tx_lft_rq   [7:0];
    logic [15:0]    sys_tx_lft_data [7:0];
    logic           sys_tx_lft_gt   [7:0];

    logic           sys_rx_rgt_rq   [7:0];
    logic [15:0]    sys_rx_rgt_data [7:0];
    logic           sys_rx_rgt_gt   [7:0];

    logic           sys_tx_rgt_rq   [7:0];
    logic [15:0]    sys_tx_rgt_data [7:0];
    logic           sys_tx_rgt_gt   [7:0];

    // input stream files
    int             file_col_upp [7:0];
    int             fstatus_col_upp [7:0];

    // router drivers
    logic [3:0]     id_col_upp [7:0];
    logic           mode_col_upp [7:0];
    logic [3:0]     addr_col_upp [7:0];
    logic [15:0]    data_col_upp [7:0];

    // cordic inputs
    logic [15:0]    cordic_inputs [0:15];

    pe_array i_pe_array (
        .clk                  (clk                ),
        .rst_n                (rst_n              ),
        .rtr_rx_col_dwn_rq_i  (rtr_rx_col_dwn_rq  ),
        .rtr_rx_col_dwn_id_i  (rtr_rx_col_dwn_id  ),
        .rtr_rx_col_dwn_mode_i(rtr_rx_col_dwn_mode),
        .rtr_rx_col_dwn_addr_i(rtr_rx_col_dwn_addr),
        .rtr_rx_col_dwn_data_i(rtr_rx_col_dwn_data),
        .rtr_rx_col_dwn_gt_o  (rtr_rx_col_dwn_gt  ),
        .rtr_tx_col_upp_rq_o  (rtr_tx_col_upp_rq  ),
        .rtr_tx_col_upp_id_o  (rtr_tx_col_upp_id  ),
        .rtr_tx_col_upp_mode_o(rtr_tx_col_upp_mode),
        .rtr_tx_col_upp_addr_o(rtr_tx_col_upp_addr),
        .rtr_tx_col_upp_data_o(rtr_tx_col_upp_data),
        .rtr_tx_col_upp_gt_i  (rtr_tx_col_upp_gt  ),
        .rtr_rx_col_upp_rq_i  (rtr_rx_col_upp_rq  ),
        .rtr_rx_col_upp_id_i  (rtr_rx_col_upp_id  ),
        .rtr_rx_col_upp_mode_i(rtr_rx_col_upp_mode),
        .rtr_rx_col_upp_addr_i(rtr_rx_col_upp_addr),
        .rtr_rx_col_upp_data_i(rtr_rx_col_upp_data),
        .rtr_rx_col_upp_gt_o  (rtr_rx_col_upp_gt  ),
        .rtr_tx_col_dwn_rq_o  (rtr_tx_col_dwn_rq  ),
        .rtr_tx_col_dwn_id_o  (rtr_tx_col_dwn_id  ),
        .rtr_tx_col_dwn_mode_o(rtr_tx_col_dwn_mode),
        .rtr_tx_col_dwn_addr_o(rtr_tx_col_dwn_addr),
        .rtr_tx_col_dwn_data_o(rtr_tx_col_dwn_data),
        .rtr_tx_col_dwn_gt_i  (rtr_tx_col_dwn_gt  ),
        .rtr_rx_row_rgt_rq_i  (rtr_rx_row_rgt_rq  ),
        .rtr_rx_row_rgt_id_i  (rtr_rx_row_rgt_id  ),
        .rtr_rx_row_rgt_mode_i(rtr_rx_row_rgt_mode),
        .rtr_rx_row_rgt_addr_i(rtr_rx_row_rgt_addr),
        .rtr_rx_row_rgt_data_i(rtr_rx_row_rgt_data),
        .rtr_rx_row_rgt_gt_o  (rtr_rx_row_rgt_gt  ),
        .rtr_tx_row_lft_rq_o  (rtr_tx_row_lft_rq  ),
        .rtr_tx_row_lft_id_o  (rtr_tx_row_lft_id  ),
        .rtr_tx_row_lft_mode_o(rtr_tx_row_lft_mode),
        .rtr_tx_row_lft_addr_o(rtr_tx_row_lft_addr),
        .rtr_tx_row_lft_data_o(rtr_tx_row_lft_data),
        .rtr_tx_row_lft_gt_i  (rtr_tx_row_lft_gt  ),
        .rtr_rx_row_lft_rq_i  (rtr_rx_row_lft_rq  ),
        .rtr_rx_row_lft_id_i  (rtr_rx_row_lft_id  ),
        .rtr_rx_row_lft_mode_i(rtr_rx_row_lft_mode),
        .rtr_rx_row_lft_addr_i(rtr_rx_row_lft_addr),
        .rtr_rx_row_lft_data_i(rtr_rx_row_lft_data),
        .rtr_rx_row_lft_gt_o  (rtr_rx_row_lft_gt  ),
        .rtr_tx_row_rgt_rq_o  (rtr_tx_row_rgt_rq  ),
        .rtr_tx_row_rgt_id_o  (rtr_tx_row_rgt_id  ),
        .rtr_tx_row_rgt_mode_o(rtr_tx_row_rgt_mode),
        .rtr_tx_row_rgt_addr_o(rtr_tx_row_rgt_addr),
        .rtr_tx_row_rgt_data_o(rtr_tx_row_rgt_data),
        .rtr_tx_row_rgt_gt_i  (rtr_tx_row_rgt_gt  ),
        .sys_rx_top_rq_i      (sys_rx_top_rq      ),
        .sys_rx_top_data_i    (sys_rx_top_data    ),
        .sys_rx_top_gt_o      (sys_rx_top_gt      ),
        .sys_tx_top_rq_o      (sys_tx_top_rq      ),
        .sys_tx_top_data_o    (sys_tx_top_data    ),
        .sys_tx_top_gt_i      (sys_tx_top_gt      ),
        .sys_rx_btm_rq_i      (sys_rx_btm_rq      ),
        .sys_rx_btm_data_i    (sys_rx_btm_data    ),
        .sys_rx_btm_gt_o      (sys_rx_btm_gt      ),
        .sys_tx_btm_rq_o      (sys_tx_btm_rq      ),
        .sys_tx_btm_data_o    (sys_tx_btm_data    ),
        .sys_tx_btm_gt_i      (sys_tx_btm_gt      ),
        .sys_rx_lft_rq_i      (sys_rx_lft_rq      ),
        .sys_rx_lft_data_i    (sys_rx_lft_data    ),
        .sys_rx_lft_gt_o      (sys_rx_lft_gt      ),
        .sys_tx_lft_rq_o      (sys_tx_lft_rq      ),
        .sys_tx_lft_data_o    (sys_tx_lft_data    ),
        .sys_tx_lft_gt_i      (sys_tx_lft_gt      ),
        .sys_rx_rgt_rq_i      (sys_rx_rgt_rq      ),
        .sys_rx_rgt_data_i    (sys_rx_rgt_data    ),
        .sys_rx_rgt_gt_o      (sys_rx_rgt_gt      ),
        .sys_tx_rgt_rq_o      (sys_tx_rgt_rq      ),
        .sys_tx_rgt_data_o    (sys_tx_rgt_data    ),
        .sys_tx_rgt_gt_i      (sys_tx_rgt_gt      )
    );

    initial begin
        forever begin
            #(CLOCKCYCLE/2.0) clk = !clk;
        end
    end

    initial begin
        $vcdpluson;

        clk   = '0;
        rst_n = '0;

        for (int i=0; i<8; i=i+1) begin
            // rx col dwn
            rtr_rx_col_dwn_rq[i]   = '0;
            rtr_rx_col_dwn_id[i]   = '0;
            rtr_rx_col_dwn_mode[i] = '0;
            rtr_rx_col_dwn_addr[i] = '0;
            rtr_rx_col_dwn_data[i] = '0;
            // rx col upp
            rtr_rx_col_upp_rq[i]   = '0;
            rtr_rx_col_upp_id[i]   = '0;
            rtr_rx_col_upp_mode[i] = '0;
            rtr_rx_col_upp_addr[i] = '0;
            rtr_rx_col_upp_data[i] = '0;
            // rx row rgt
            rtr_rx_row_rgt_rq[i]   = '0;
            rtr_rx_row_rgt_id[i]   = '0;
            rtr_rx_row_rgt_mode[i] = '0;
            rtr_rx_row_rgt_addr[i] = '0;
            rtr_rx_row_rgt_data[i] = '0;
            // rx row lft
            rtr_rx_row_lft_rq[i]   = '0;
            rtr_rx_row_lft_id[i]   = '0;
            rtr_rx_row_lft_mode[i] = '0;
            rtr_rx_row_lft_addr[i] = '0;
            rtr_rx_row_lft_data[i] = '0;

            // tx col upp
            rtr_tx_col_upp_gt[i] = '0;
            // tx col dwn
            rtr_tx_col_dwn_gt[i] = '0;
            // tx row lft
            rtr_tx_row_lft_gt[i] = '0;
            // tx row rgt
            rtr_tx_row_rgt_gt[i] = '0;

            // rx top
            sys_rx_top_rq[i]   = '0;
            sys_rx_top_data[i] = '0;
            // rx btm
            sys_rx_btm_rq[i]   = '0;
            sys_rx_btm_data[i] = '0;
            // rx lft
            sys_rx_lft_rq[i]   = '0;
            sys_rx_lft_data[i] = '0;
            // rx rgt
            sys_rx_rgt_rq[i]   = '0;
            sys_rx_rgt_data[i] = '0;

            // tx top
            sys_tx_top_gt[i] = '0;
            // tx btm
            sys_tx_btm_gt[i] = '0;
            // tx lft
            sys_tx_lft_gt[i] = '0;
            // tx rgt
            sys_tx_rgt_gt[i] = '0;
        end

        repeat(5) @(negedge clk);
        rst_n = 1'b1;
        @(negedge clk);
        for (int i=0; i<8; i=i+1) begin
            // tx col upp
            rtr_tx_col_upp_gt[i] = 1'b1;
            // tx col dwn
            rtr_tx_col_dwn_gt[i] = 1'b1;
            // tx row lft
            rtr_tx_row_lft_gt[i] = 1'b1;
            // tx row rgt
            rtr_tx_row_rgt_gt[i] = 1'b1;

            // tx top
            sys_tx_top_gt[i] = 1'b1;
            // tx btm
            sys_tx_btm_gt[i] = 1'b1;
            // tx lft
            sys_tx_lft_gt[i] = 1'b1;
            // tx rgt
            sys_tx_rgt_gt[i] = 1'b1;
        end

        fork
            begin // for isolation
                for (int i=0; i<8; i=i+1) begin
                    automatic int j = i;
                    fork
                        begin
                            file_col_upp[j] = $fopen($sformatf("../../tb/pe_array/cordic_hyperbolic_rotation/file_col_upp_%1d.mem", j), "r");
                            forever begin
                                fstatus_col_upp[j] = $fscanf(file_col_upp[j], "id = %h, mode = %b, addr = %h, data = %h", id_col_upp[j], mode_col_upp[j], addr_col_upp[j], data_col_upp[j]);
                                if(fstatus_col_upp[j] == -1) begin
                                    $fclose(file_col_upp[j]);
                                    break;
                                end
                                else begin
                                    @(negedge clk);
                                    rtr_rx_col_upp_rq[j]   = 1'b1;
                                    rtr_rx_col_upp_id[j]   = id_col_upp[j];
                                    rtr_rx_col_upp_mode[j] = mode_col_upp[j];
                                    rtr_rx_col_upp_addr[j] = addr_col_upp[j];
                                    rtr_rx_col_upp_data[j] = data_col_upp[j];
                                    forever begin
                                        @(posedge clk);
                                        if (rtr_rx_col_upp_gt[j]) break;
                                    end
                                end
                            end
                            @(negedge clk);
                            rtr_rx_col_upp_rq[j]   = 1'b0;
                            rtr_rx_col_upp_id[j]   = '0;
                            rtr_rx_col_upp_mode[j] = '0;
                            rtr_rx_col_upp_addr[j] = '0;
                            rtr_rx_col_upp_data[j] = '0;
                        end
                    join_none
                end

                wait fork;
            end // for isolation
        join

        cordic_inputs = {
            16'h625d, 16'h0000, // xin_0, dummy
            16'h3e00, 16'h60f1, // zin_0, yin_0
            16'h6314, 16'h0000, // xin_1, dummy
            16'h38e1, 16'h5619, // zin_1, yin_1
            16'h5d1c, 16'h0000, // xin_2, dummy
            16'h3400, 16'h5c5a, // zin_2, yin_2
            16'h6323, 16'h0000, // xin_3, dummy
            16'h3ce1, 16'h6046  // zin_3, yin_3
        };

        //fft
        fork
            begin // for isolation
                for (int i=0; i<8; i=i+1) begin
                    automatic int j = i;
                    fork
                        begin
                            @(negedge clk);
                            sys_rx_lft_rq[j]   = 1'b1;
                            sys_rx_lft_data[j] = cordic_inputs[2*j];
                            forever begin
                                @(posedge clk);
                                if (sys_rx_lft_gt[j]) break;
                            end
                            @(negedge clk);
                            if (j % 2 == 0) begin
                                sys_rx_lft_rq[j]   = 1'b0;
                                sys_rx_lft_data[j] = '0;
                            end
                            else begin
                                sys_rx_lft_rq[j]   = 1'b1;
                                sys_rx_lft_data[j] = cordic_inputs[2*j+1];
                            end
                            forever begin
                                @(posedge clk);
                                if (sys_rx_lft_gt[j]) break;
                            end
                            @(negedge clk);
                            sys_rx_lft_rq[j]   = 1'b0;
                            sys_rx_lft_data[j] = '0;
                        end
                    join_none
                end
                wait fork;
            end // for isolation
        join

        fork
            begin
                for (int i=0; i<8; i=i+1) begin
                    automatic int j = i;
                    fork
                        begin
                            forever begin
                                @(posedge clk);
                                if (sys_tx_rgt_rq[j] && sys_tx_rgt_rq[j])
                                    $display("sys_tx_rgt_data[%1d] = %h", j, sys_tx_rgt_data[j]);
                            end
                        end
                    join_none
                end
                wait fork;
            end
        join

    end

    initial begin
        repeat(400) @(negedge clk);
        $finish;
    end

endmodule : tb_pe_array_cordic_hyperbolic_rotation
